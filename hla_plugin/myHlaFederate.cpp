#include "myHlaFederate.h"



myHlaFederate::myHlaFederate()
{
}

myHlaFederate::myHlaFederate(ofstream *logFile)
{
	_log = logFile;
}


myHlaFederate::~myHlaFederate()
{
}

//add date to message
void myHlaFederate::log(string logMessage) {
	*_log << logMessage << endl;
	_log->flush();
}

void myHlaFederate::log(wstring logMessage)
{
	*_log << logMessage.c_str() << endl;
	_log->flush();
}

////////////////////
// connect to rti//
///////////////////
void myHlaFederate::connect(wstring FOM, wstring localSetting, wstring federationName, wstring federateName)
{
	log("startint connecting");
	try {
		shared_ptr<RTIambassadorFactory> rtiAmbassadorFactory(new RTIambassadorFactory());
		_rtiAmbassador = rtiAmbassadorFactory->createRTIambassador();
	}
	catch (const rti1516e::Exception& e) {
		log(e.what());
		throw;
	}
	log("created rti ambassador ");

	try {
		_rtiAmbassador->connect(*this, HLA_IMMEDIATE, localSetting);
	}
	catch (const rti1516e::Exception& e) {
		log(e.what());
		throw;
	}

	log("connected to RTI ");

	try {
		_rtiAmbassador->destroyFederationExecution(federationName);
	}
	catch (const rti1516e::FederatesCurrentlyJoined& e) {
		log( e.what());
	}
	catch (const rti1516e::FederationExecutionDoesNotExist& e) {
		log(e.what());
	}
	catch (const rti1516e::RTIinternalError& e) {
		log(e.what());
	}

	log("after destroy federation");
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
		log("exception in createFederation");
		*_log << e.what().c_str();
		log(e.what());
		throw;
	}
	log("created federation execution");

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
	log("Joined ");
}


////////////////////////////////////////////////////
//  Implementation methods to remove object event //
////////////////////////////////////////////////////
void myHlaFederate::removeVehicle(VehicleData vehicleData)
{
	vector<Vehicle>::iterator it;
	it = std::find_if(_vehicles.begin(), _vehicles.end(), [&](Vehicle const& obj) {
		return obj.ID == vehicleData.ID;
	});

	if (it != _vehicles.end()) {
		_rtiAmbassador->deleteObjectInstance(it->hlaInstanceHandle, VariableLengthData());
		_vehicles.erase(it);		
	}
	else {
		log("don't find any object in players - update vehicle");
	}
}

void myHlaFederate::removePlayer(PlayerData playerData)
{
	vector<Player>::iterator it;
	it = std::find_if(_players.begin(), _players.end(), [&](Player const& obj) {
		return obj.ID == playerData.ID;
	});

	if (it != _players.end()) {
		_rtiAmbassador->deleteObjectInstance(it->hlaInstanceHandle, VariableLengthData());
		_players.erase(it);
	}
	else {
		log("don't find any object in players - update vehicle");
	}
}
//////////////////////////////////////////////////////////////
//  Implementation methods to create object event. Return id//
//////////////////////////////////////////////////////////////

int myHlaFederate::createVehicle()
{
	ObjectInstanceHandle theObject = _rtiAmbassador->registerObjectInstance(Vehicle::handle);
	Vehicle *newVehicle = new Vehicle(theObject);
	_vehicles.push_back(*newVehicle);
	return newVehicle->ID;
}

int myHlaFederate::createPlayer()
{
	ObjectInstanceHandle theObject = _rtiAmbassador->registerObjectInstance(Player::handle);
	Player *newPlayer = new Player(theObject);
	_players.push_back(*newPlayer);
	return newPlayer->ID;
}

//////////////////////////////////////////////////////
//  Implementation methods to publish object event. //
//////////////////////////////////////////////////////
void myHlaFederate::publishVehicle()
{
	log("Publish vehicle");
	if (!Vehicle::initiated) {
		Vehicle::InitClass(_rtiAmbassador);
		log("Initialiazd vehicle");
	}
	AttributeHandleSet vehicleAttribiute;
	Vehicle::getAttribiuteSet(&vehicleAttribiute);

	_rtiAmbassador->publishObjectClassAttributes(Vehicle::handle, vehicleAttribiute);
	log("published vehicle");
}

void myHlaFederate::publishPlayer()
{
	log("publishe player");
	if (!Player::initiated) {
		Player::InitClass(_rtiAmbassador);
		log("Initialiazd player");
	}
	AttributeHandleSet playerAttribiute;
	Player::getAttribiuteSet(&playerAttribiute);

	_rtiAmbassador->publishObjectClassAttributes(Player::handle, playerAttribiute);
	log("published player");
}

//////////////////////////////////////////////////////
//  Implementation methods to subscrib object event//
/////////////////////////////////////////////////////
void myHlaFederate::subscribeVehicle()
{
	log("Subscribe vehicle");
	if (!Vehicle::initiated) {
		Vehicle::InitClass(_rtiAmbassador);
		log("Initialiazd vehicle");
	}
	AttributeHandleSet vehicleAttribiute;
	Vehicle::getAttribiuteSet(&vehicleAttribiute);

	_rtiAmbassador->subscribeObjectClassAttributes(Vehicle::handle, vehicleAttribiute);
	log("Subscribed vehicle");
}

void myHlaFederate::subscribePlayer()
{
	log("Subscribe player");
	if (!Player::initiated) {
		Player::InitClass(_rtiAmbassador);
		log("Initialiazd player");
	}
	AttributeHandleSet playerAttribiute;
	Player::getAttribiuteSet(&playerAttribiute);

	_rtiAmbassador->subscribeObjectClassAttributes(Player::handle, playerAttribiute);
	log("Subscribe player");
}


////////////////////////////////////////////////////
//  Implementation methods to send update event  //
///////////////////////////////////////////////////


void myHlaFederate::updateVehicle(VehicleData vehicleData)
{
	vector<Vehicle>::iterator it;
	it = std::find_if(_vehicles.begin(), _vehicles.end(), [&](Vehicle const& obj) {
		return obj.ID == vehicleData.ID;
	});

	if (it != _vehicles.end()) {
		it->setVehicleData(vehicleData);
		AttributeHandleValueMap attributeMap;
		it->getAttribiuteMap(&attributeMap);
		_rtiAmbassador->updateAttributeValues(it->hlaInstanceHandle, attributeMap, VariableLengthData());
	}
	else {
		log("don't find any object in players - update vehicle");
	}
}

void myHlaFederate::updatePlayer(PlayerData playerData)
{
	vector<Player>::iterator it;
	it = std::find_if(_players.begin(), _players.end(), [&](Player const& obj) {
		return obj.ID == playerData.ID;
	});

	if (it != _players.end()) {
		it->setPlayerData(playerData);
		AttributeHandleValueMap attributeMap;
		it->getAttribiuteMap(&attributeMap);
		_rtiAmbassador->updateAttributeValues(it->hlaInstanceHandle, attributeMap, VariableLengthData());
	}
	else {
		log("don't find any object in players - update player");
	}
}

////////////////////////////////////////////////////////
//  Implementation methods to handle discovery event //
///////////////////////////////////////////////////////
void myHlaFederate::discoverObjectInstanceImpl(
	ObjectInstanceHandle theObject,
	ObjectClassHandle theObjectClass)
	throw (
		FederateInternalError) {

	if (theObjectClass == Vehicle::handle) {
		Vehicle *newVehicle = new Vehicle(theObject);
		_vehicles.push_back(*newVehicle);
	}
	else if (theObjectClass == Player::handle) {
		Player *newPlayer = new Player(theObject);
		_players.push_back(*newPlayer);
	}
	else {
		log("Don't recognize object class in discover");
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

	ObjectClassHandle theObjectClass = _rtiAmbassador->getKnownObjectClassHandle(theObject);
	if (theObjectClass == Vehicle::handle) {
		vector<Vehicle>::iterator it;
		it = std::find_if(_vehicles.begin(), _vehicles.end(), [&](Vehicle const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _vehicles.end()) {
			it->updateAttribiutes(theAttributeValues);
		}
			
		else {
			log("don't find any object in vehicle - reflect atribiute");
		}		

	}
	else if (theObjectClass == Player::handle) {
		vector<Player>::iterator it;
		it = std::find_if(_players.begin(), _players.end(), [&](Player const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _players.end()) {
			it->updateAttribiutes(theAttributeValues);
		}
		else {
			log("don't find any object in players - reflect atribiute");
		}
	}
	else {
		log("Don't recognize object class in reflected atribiute");
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
	log("receive interaction but nothing doing with it");
}

////////////////////////////////////////////////////////////
//  Implementation methods to handle remove object event //
///////////////////////////////////////////////////////////
void myHlaFederate::removeObjectInstanceImpl(
	ObjectInstanceHandle theObject)
	throw (
		FederateInternalError) {
	ObjectClassHandle theObjectClass = _rtiAmbassador->getKnownObjectClassHandle(theObject);
	if (theObjectClass == Vehicle::handle) {
		vector<Vehicle>::iterator it;
		it = std::find_if(_vehicles.begin(), _vehicles.end(), [&](Vehicle const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _vehicles.end()) {
			_vehicles.erase(it);
		}

		else {
			log("don't find any object in vehicle - remove object");
		}

	}
	else if (theObjectClass == Player::handle) {
		vector<Player>::iterator it;
		it = std::find_if(_players.begin(), _players.end(), [&](Player const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _players.end()) {
			_players.erase(it);
		}
		else {
			log("don't find any object in players - remove object");
		}
	}
	else {
		log("Don't recognize object class in remove object");
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

	ObjectClassHandle theObjectClass = _rtiAmbassador->getKnownObjectClassHandle(theObject);
	AttributeHandleValueMap attributeMap;

	if (theObjectClass == Vehicle::handle) {
		vector<Vehicle>::iterator it;
		it = std::find_if(_vehicles.begin(), _vehicles.end(), [&](Vehicle const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _vehicles.end()) {
			it->getAttribiuteMap(theAttributes,&attributeMap);
			_rtiAmbassador->updateAttributeValues(theObject, attributeMap, VariableLengthData());
		}

		else {
			log("don't find any object in vehicle - reflect atribiute");
		}

	}
	else if (theObjectClass == Player::handle) {
		vector<Player>::iterator it;
		it = std::find_if(_players.begin(), _players.end(), [&](Player const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _players.end()) {
			it->getAttribiuteMap(theAttributes, &attributeMap);
			_rtiAmbassador->updateAttributeValues(theObject, attributeMap, VariableLengthData());
		}
		else {
			log("don't find any object in players - reflect atribiute");
		}
	}
	else {
		log("Don't recognize object class in reflected atribiute");
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
		FederateInternalError) {provideAttributeValueUpdateImpl(theObject, theAttributes);}