#include "myHlaFederate.h"


myHlaFederate::myHlaFederate()
{
	_connect = false;
}



myHlaFederate::~myHlaFederate()
{
}



////////////////////
// connect to rti//
///////////////////
void myHlaFederate::connect(wstring FOM, wstring localSetting, wstring federationName, wstring federateName)
{
	Debug::Log("startint connecting");
	_federationName = federationName;
	try {
		shared_ptr<RTIambassadorFactory> rtiAmbassadorFactory(new RTIambassadorFactory());
		_rtiAmbassador = rtiAmbassadorFactory->createRTIambassador();
	}
	catch (const rti1516e::Exception& e) {
		Debug::Log(e.what());
		throw;
	}
	Debug::Log("created rti ambassador ");

	try {
		_rtiAmbassador->connect(*this, HLA_IMMEDIATE, localSetting);
	}
	catch (const rti1516e::Exception& e) {
		Debug::Log(e.what());
		throw;
	}

	Debug::Log("connected to RTI ");

	try {
		_rtiAmbassador->destroyFederationExecution(federationName);
	}
	catch (const rti1516e::FederatesCurrentlyJoined& e) {
		Debug::Log( e.what());
	}
	catch (const rti1516e::FederationExecutionDoesNotExist& e) {
		Debug::Log(e.what());
	}
	catch (const rti1516e::RTIinternalError& e) {
		Debug::Log(e.what());
	}

	Debug::Log("after destroy federation");
	// Always try and create the federation execution.
	// We do this because we have no special federate that has the responsibility
	// to create the federation execution. Make sure to catch the exception!
	try {
		_rtiAmbassador->createFederationExecution(federationName, FOM);
	}
	catch (const FederationExecutionAlreadyExists&) {
		// the federation execution already exist so ignore
	}
	catch (const rti1516e::Exception& e) {
		Debug::Log("exception in createFederation");
		Debug::Log(e.what());
		throw;
	}
	Debug::Log("created federation execution");

	// Join the federation. If the federate name is taken add a sequence 
	// number to it to make it unique and try again. 
	bool joined = false;
	int sequenceNumber = 1;
	wstring uniqueName = federateName;

	while (!joined) {
		try {
			FederateHandle federateHandle = _rtiAmbassador->joinFederationExecution(federateName, federationName);

			joined = true;
			federateName = uniqueName;

		}
		catch (const rti1516e::FederateNameAlreadyInUse&) {
			uniqueName = federateName + L"-";
			++sequenceNumber;
		}
	}
	_connect = true;
	Debug::Log("Joined ");
}

void myHlaFederate::disconnect()
{
	if (_connect) {
		// When we disconnect from the federation execution we want to: 
		//  - Cancel any pending ownership acquisitions
		//  - Delete the objects created by us
		//  - Divest any owned attributes
		try {
			_rtiAmbassador->resignFederationExecution(CANCEL_THEN_DELETE_THEN_DIVEST);

			// we don't have to handle these exceptions
		}
		catch (const rti1516e::InvalidResignAction&) {
		}
		catch (const rti1516e::OwnershipAcquisitionPending&) {
		}
		catch (const rti1516e::FederateOwnsAttributes&) {
		}
		catch (const rti1516e::FederateNotExecutionMember&) {
		}
		catch (const rti1516e::NotConnected&) {
		}
		catch (const rti1516e::CallNotAllowedFromWithinCallback&) {
		}
		catch (const rti1516e::RTIinternalError&) {
		}

		// Just as we try and create the federation execution we will try and 
		// destroy it since we cannot know if we're the last one to resign.
		try {
			_rtiAmbassador->destroyFederationExecution(_federationName);

			// we don't have to handle these exceptions
		}
		catch (const rti1516e::FederatesCurrentlyJoined&) {
		}
		catch (const rti1516e::FederationExecutionDoesNotExist&) {
		}
		catch (const rti1516e::NotConnected&) {
		}
		catch (const rti1516e::RTIinternalError&) {
		}

		// Finally disconnect from the federation
		try {
			_rtiAmbassador->disconnect();

			// we don't have to handle these exceptions
		}
		catch (const rti1516e::FederateIsExecutionMember&) {
		}
		catch (const rti1516e::CallNotAllowedFromWithinCallback&) {
		}
		catch (const rti1516e::RTIinternalError&) {
		}
	}
}

vector<Vehicle> myHlaFederate::getVehicles()
{
	return _vehicles;
}

vector<Player> myHlaFederate::getPlayers()
{
	return _players;
}

vector<shotInteraction> myHlaFederate::getShots()
{
	vector<shotInteraction> toReturn = _shots;
	_shots.clear();
	return toReturn;
}


////////////////////////////////////////////////////
//  Implementation methods to remove object event //
////////////////////////////////////////////////////
void myHlaFederate::removeVehicle(VehicleData vehicleData)
{
	Debug::Log("remove vehicle");
	vector<Vehicle>::iterator it;
	it = std::find_if(_vehicles.begin(), _vehicles.end(), [&](Vehicle const& obj) {
		return obj.ID == vehicleData.ID;
	});

	if (it != _vehicles.end()) {
		_rtiAmbassador->deleteObjectInstance(it->hlaInstanceHandle, VariableLengthData());
		_vehicles.erase(it);		
	}
	else {
		Debug::Log("don't find any object in players - update vehicle");
	}
}

void myHlaFederate::removePlayer(PlayerData playerData)
{
	Debug::Log("remove player");
	vector<Player>::iterator it;
	it = std::find_if(_players.begin(), _players.end(), [&](Player const& obj) {
		return obj.ID == playerData.ID;
	});

	if (it != _players.end()) {
		_rtiAmbassador->deleteObjectInstance(it->hlaInstanceHandle, VariableLengthData());
		_players.erase(it);
	}
	else {
		Debug::Log("don't find any object in players - update vehicle");
	}
}
//////////////////////////////////////////////////////////////
//  Implementation methods to create object event. Return id//
//////////////////////////////////////////////////////////////

int myHlaFederate::createVehicle()
{
	Debug::Log("create Vehicle");
	ObjectInstanceHandle theObject = _rtiAmbassador->registerObjectInstance(Vehicle::vehicleClassHandle);
	Vehicle newVehicle(theObject);
	_vehicles.push_back(newVehicle);
	Debug::Log("created Vehicle: ", newVehicle.ID);
	return newVehicle.ID;
}

int myHlaFederate::createPlayer()
{
		Debug::Log("create Player");
		ObjectInstanceHandle theObject = _rtiAmbassador->registerObjectInstance(Player::playerClassHandle);
		Player newPlayer(theObject);
		_players.push_back(newPlayer);
		Debug::Log("created Player: ",newPlayer.ID);
		return newPlayer.ID;

}

//////////////////////////////////////////////////////
//  Implementation methods to publish object event. //
//////////////////////////////////////////////////////
void myHlaFederate::publishVehicle()
{
	Debug::Log("Publish vehicle");
	if (!Vehicle::initiated) {
		Vehicle::init(_rtiAmbassador);
		Debug::Log("Initialiazd vehicle");
	}
	AttributeHandleSet vehicleAttribiute;
	Vehicle::getAttribiuteSet(&vehicleAttribiute);

	_rtiAmbassador->publishObjectClassAttributes(Vehicle::vehicleClassHandle, vehicleAttribiute);
	Debug::Log("published vehicle");
}

void myHlaFederate::publishPlayer()
{
	try {
		Debug::Log("publishe player");
		if (!Player::initiated) {
			Player::init(_rtiAmbassador);
			Debug::Log("Initialiazd player");
		}
		AttributeHandleSet playerAttribiute;
		Player::getAttribiuteSet(&playerAttribiute);

		_rtiAmbassador->publishObjectClassAttributes(Player::playerClassHandle, playerAttribiute);
		Debug::Log("published player");
	}
	catch (const Exception& e) {
		Debug::Log(e.what());
	}
}

void myHlaFederate::publishShot()
{
	try {
		Debug::Log("publishe shot");
		if (!shotInteraction::initied) {
			shotInteraction::init(_rtiAmbassador);
			Debug::Log("Initialiazd shot");
		}
		_rtiAmbassador->publishInteractionClass(shotInteraction::shotClassHandle);
		Debug::Log("published shot");
	}
	catch (const Exception& e) {
		Debug::Log(e.what());
	}
}

//////////////////////////////////////////////////////
//  Implementation methods to subscrib object event//
/////////////////////////////////////////////////////
void myHlaFederate::subscribeVehicle()
{
	Debug::Log("Subscribe vehicle");
	if (!Vehicle::initiated) {
		Vehicle::init(_rtiAmbassador);
		Debug::Log("Initialiazd vehicle");
	}
	AttributeHandleSet vehicleAttribiute;
	Vehicle::getAttribiuteSet(&vehicleAttribiute);

	_rtiAmbassador->subscribeObjectClassAttributes(Vehicle::vehicleClassHandle, vehicleAttribiute);
	Debug::Log("Subscribed vehicle");
}

void myHlaFederate::subscribePlayer()
{
	Debug::Log("Subscribe player");
	if (!Player::initiated) {
		Player::init(_rtiAmbassador);
		Debug::Log("Initialiazd player");
	}
	AttributeHandleSet playerAttribiute;
	Player::getAttribiuteSet(&playerAttribiute);

	_rtiAmbassador->subscribeObjectClassAttributes(Player::playerClassHandle, playerAttribiute);
	Debug::Log("Subscribe player");
}

void myHlaFederate::subscribeShot()
{
	try {
		Debug::Log("subscribe shot");
		if (!shotInteraction::initied) {
			shotInteraction::init(_rtiAmbassador);
			Debug::Log("Initialiazd shot");
		}
		_rtiAmbassador->subscribeInteractionClass(shotInteraction::shotClassHandle);
		Debug::Log("subscribe shot");
	}
	catch (const Exception& e) {
		Debug::Log(e.what());
	}
}


////////////////////////////////////////////////////
//  Implementation methods to send update event  //
///////////////////////////////////////////////////


void myHlaFederate::updateVehicle(VehicleData vehicleData)
{
	Debug::Log("update vehicle: ", vehicleData.ID);
	vector<Vehicle>::iterator it;
	it = std::find_if(_vehicles.begin(), _vehicles.end(), [&](Vehicle const& obj) {
		return obj.ID == vehicleData.ID;
	});

	if (it != _vehicles.end()) {
		it->setVehicleData(vehicleData);
		AttributeHandleValueMap attributeMap;
		it->getAttribiuteMap(&attributeMap);
		_rtiAmbassador->updateAttributeValues(it->hlaInstanceHandle, attributeMap, VariableLengthData());
		Debug::Log("updated vehicle");
	}
	else {
		Debug::Log("don't find any object in players - update vehicle");
	}
}

void myHlaFederate::updatePlayer(PlayerData playerData)
{
	Debug::Log("update player: ",playerData.ID);
	vector<Player>::iterator it;
	it = std::find_if(_players.begin(), _players.end(), [&](Player const& obj) {
		return obj.ID == playerData.ID;
	});
	if (it != _players.end()) {
		it->setPlayerData(playerData);
		AttributeHandleValueMap attributeMap;
		it->getAttribiuteMap(&attributeMap);
		_rtiAmbassador->updateAttributeValues(it->hlaInstanceHandle, attributeMap, VariableLengthData());
		Debug::Log("updated player");
	}
	else {
		Debug::Log("don't find any object in players - update player");
	}
}

void myHlaFederate::sentShot(ShotData shotData)
{
	shotInteraction tmp = shotInteraction(shotData);
	ParameterHandleValueMap toSend;
	tmp.getParameterMap(&toSend);
	_rtiAmbassador->sendInteraction(shotInteraction::shotClassHandle, toSend, VariableLengthData());
}

////////////////////////////////////////////////////////
//  Implementation methods to handle discovery event //
///////////////////////////////////////////////////////
void myHlaFederate::discoverObjectInstanceImpl(
	ObjectInstanceHandle theObject,
	ObjectClassHandle theObjectClass)
	throw (
		FederateInternalError) {
	Debug::Log("discovery object");
	if (theObjectClass == Vehicle::vehicleClassHandle) {
		Vehicle newVehicle(theObject);
		_vehicles.push_back(newVehicle);
	}
	else if (theObjectClass == Player::playerClassHandle) {
		Player newPlayer(theObject);
		_players.push_back(newPlayer);
	}
	else {
		Debug::Log("Don't recognize object class in discover");
	}
}

////////////////////////////////////////////////////////
//  Implementation methods to handle reflect event //
///////////////////////////////////////////////////////
void myHlaFederate::reflectAttributeValuesImpl(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues)
	throw (
		FederateInternalError) {
	Debug::Log("reflect Attribiute value");
	ObjectClassHandle theObjectClass = _rtiAmbassador->getKnownObjectClassHandle(theObject);
	if (theObjectClass == Vehicle::vehicleClassHandle) {
		Debug::Log("reflect Attribiute for vehicle");
		vector<Vehicle>::iterator it;
		it = std::find_if(_vehicles.begin(), _vehicles.end(), [&](Vehicle const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _vehicles.end()) {
			Debug::Log("Update attribiute vehicle: ", it->ID);
			it->updateAttribiutes(theAttributeValues);
		}
			
		else {
			Debug::Log("don't find any object in vehicle - reflect atribiute");
		}		

	}
	else if (theObjectClass == Player::playerClassHandle) {
		Debug::Log("reflect Attribiute for player");
		vector<Player>::iterator it;
		it = std::find_if(_players.begin(), _players.end(), [&](Player const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _players.end()) {
			it->updateAttribiutes(theAttributeValues);
		}
		else {
			Debug::Log("don't find any object in players - reflect atribiute");
		}
	}
	else {
		Debug::Log("Don't recognize object class in reflected atribiute");
	}
}

/////////////////////////////////////////////////////////////////
//  Implementation methods to handle receive interaction event //
/////////////////////////////////////////////////////////////////

//TODO when we have interaction
void myHlaFederate::receiveInteractionImpl(
	InteractionClassHandle theInteraction,
	ParameterHandleValueMap const & theParameterValues)
	throw (
		FederateInternalError) {
	Debug::Log("receive interaction ");
	if (theInteraction == shotInteraction::shotClassHandle) {
		_shots.push_back(shotInteraction(theParameterValues));
	}
	else {
		Debug::Log("don't recognize interaction ");
	}
}

////////////////////////////////////////////////////////////
//  Implementation methods to handle remove object event //
///////////////////////////////////////////////////////////
void myHlaFederate::removeObjectInstanceImpl(
	ObjectInstanceHandle theObject)
	throw (
		FederateInternalError) {
	ObjectClassHandle theObjectClass = _rtiAmbassador->getKnownObjectClassHandle(theObject);
	if (theObjectClass == Vehicle::vehicleClassHandle) {
		vector<Vehicle>::iterator it;
		it = std::find_if(_vehicles.begin(), _vehicles.end(), [&](Vehicle const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _vehicles.end()) {
			_vehicles.erase(it);
		}

		else {
			Debug::Log("don't find any object in vehicle - remove object");
		}

	}
	else if (theObjectClass == Player::playerClassHandle) {
		vector<Player>::iterator it;
		it = std::find_if(_players.begin(), _players.end(), [&](Player const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _players.end()) {
			_players.erase(it);
		}
		else {
			Debug::Log("don't find any object in players - remove object");
		}
	}
	else {
		Debug::Log("Don't recognize object class in remove object");
	}
}

////////////////////////////////////////////////////////////////
//  Implementation methods to handle provide Attribute event //
///////////////////////////////////////////////////////////////
void myHlaFederate::provideAttributeValueUpdateImpl(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & theAttributes)
	throw (
		FederateInternalError) {
	Debug::Log("provide attribiute");
	ObjectClassHandle theObjectClass = _rtiAmbassador->getKnownObjectClassHandle(theObject);
	AttributeHandleValueMap attributeMap;

	if (theObjectClass == Vehicle::vehicleClassHandle) {
		vector<Vehicle>::iterator it;
		it = std::find_if(_vehicles.begin(), _vehicles.end(), [&](Vehicle const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _vehicles.end()) {
			it->getAttribiuteMap(theAttributes,&attributeMap);
			_rtiAmbassador->updateAttributeValues(theObject, attributeMap, VariableLengthData());
		}

		else {
			Debug::Log("don't find any object in vehicle - reflect atribiute");
		}

	}
	else if (theObjectClass == Player::playerClassHandle) {
		vector<Player>::iterator it;
		it = std::find_if(_players.begin(), _players.end(), [&](Player const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _players.end()) {
			it->getAttribiuteMap(theAttributes, &attributeMap);
			_rtiAmbassador->updateAttributeValues(theObject, attributeMap, VariableLengthData());
		}
		else {
			Debug::Log("don't find any object in players - reflect atribiute");
		}
	}
	else {
		Debug::Log("Don't recognize object class in reflected atribiute");
	}
}



///////////////////////////////////////////////////////////////////////////
//  Methods to recive hla event. only transmit to implementation method  //
///////////////////////////////////////////////////////////////////////////

//////////////////
//  Discovery  //
/////////////////


void myHlaFederate::discoverObjectInstance(
	ObjectInstanceHandle theObject,
	ObjectClassHandle theObjectClass,
	std::wstring const & theObjectInstanceName,
	FederateHandle producingFederate)
	throw (
		FederateInternalError){discoverObjectInstanceImpl(theObject, theObjectClass);}

void myHlaFederate::discoverObjectInstance(
	ObjectInstanceHandle theObject,
	ObjectClassHandle theObjectClass,
	std::wstring const & theObjectInstanceName)
	throw (
		FederateInternalError) {discoverObjectInstanceImpl(theObject, theObjectClass);}

////////////////
//  Reflect  //
///////////////
void myHlaFederate::reflectAttributeValues(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	SupplementalReflectInfo theReflectInfo)
	throw (
		FederateInternalError){	reflectAttributeValuesImpl(theObject, theAttributeValues);}

void myHlaFederate::reflectAttributeValues(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	SupplementalReflectInfo theReflectInfo)
	throw (
		FederateInternalError){reflectAttributeValuesImpl(theObject, theAttributeValues);}

void myHlaFederate::reflectAttributeValues(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	MessageRetractionHandle theHandle,
	SupplementalReflectInfo theReflectInfo)
	throw (
		FederateInternalError){reflectAttributeValuesImpl(theObject, theAttributeValues);}
////////////////
//  Receive  //
///////////////
void myHlaFederate::receiveInteraction(
	InteractionClassHandle theInteraction,
	ParameterHandleValueMap const & theParameterValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	SupplementalReceiveInfo theReceiveInfo)
	throw (
		FederateInternalError) {receiveInteractionImpl(theInteraction, theParameterValues);}

void myHlaFederate::receiveInteraction(
	InteractionClassHandle theInteraction,
	ParameterHandleValueMap const & theParameterValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	SupplementalReceiveInfo theReceiveInfo)
	throw (
		FederateInternalError) {receiveInteractionImpl(theInteraction, theParameterValues);}

void myHlaFederate::receiveInteraction(
	InteractionClassHandle theInteraction,
	ParameterHandleValueMap const & theParameterValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	MessageRetractionHandle theHandle,
	SupplementalReceiveInfo theReceiveInfo)
	throw (
		FederateInternalError) {receiveInteractionImpl(theInteraction, theParameterValues);}
///////////////
//  remove  //
//////////////
void myHlaFederate::removeObjectInstance(
	ObjectInstanceHandle theObject,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	SupplementalRemoveInfo theRemoveInfo)
	throw (
		FederateInternalError) {
	removeObjectInstanceImpl(theObject);
}

void myHlaFederate::removeObjectInstance(
	ObjectInstanceHandle theObject,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	SupplementalRemoveInfo theRemoveInfo)
	throw (
		FederateInternalError){removeObjectInstanceImpl(theObject);}

void myHlaFederate::removeObjectInstance(
	ObjectInstanceHandle theObject,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	MessageRetractionHandle theHandle,
	SupplementalRemoveInfo theRemoveInfo)
	throw (
		FederateInternalError){removeObjectInstanceImpl(theObject);}
///////////////
//  provide  //
//////////////
void myHlaFederate::provideAttributeValueUpdate(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & theAttributes,
	VariableLengthData const & theUserSuppliedTag)
	throw (
		FederateInternalError) {//provideAttributeValueUpdateImpl(theObject, theAttributes);
}