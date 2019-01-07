#include "myHlaFederate.h"



myHlaFederate::myHlaFederate()
{
}


myHlaFederate::~myHlaFederate()
{
}

//add date to message
void myHlaFederate::log(string logMessage) {
	_log << logMessage << endl;
	_log.flush();
}

////////////////////////////////////////////////////////
//  Implementation methods to handle discovery event //
///////////////////////////////////////////////////////
void myHlaFederate::discoverObjectInstanceImpl(
	ObjectInstanceHandle theObject,
	ObjectClassHandle theObjectClass)
	throw (
		FederateInternalError) {

	if (theObjectClass == Vehicle::vehicleHandle) {
		Vehicle *newVehicle = new Vehicle(theObject);
		_vehicles.push_back(*newVehicle);
	}
	else if (theObjectClass == Player::playerHandle) {
		Player *newPlayer = new Player(theObject);
		_players.push_back(*newPlayer);
	}
	else {
		log("Don't recognize object class in discover");
	}
}

////////////////////////////////////////////////////////
//  Implementation methods to handle discovery event //
///////////////////////////////////////////////////////
void myHlaFederate::reflectAttributeValuesImpl(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues)
	throw (
		FederateInternalError) {

	ObjectClassHandle theObjectClass = _rtiAmbassador->getKnownObjectClassHandle(theObject);
	if (theObjectClass == Vehicle::vehicleHandle) {
		vector<Vehicle>::iterator it;
		it = std::find_if(_vehicles.begin(), _vehicles.end(), [](Vehicle const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _vehicles.end()) {
			it->updateAtribiute(theAttributeValues);
		}
			
		else {
			log("don't find any object in vehicle - reflect atribiute")
		}		

	}
	else if (theObjectClass == Player::playerHandle) {
		vector<Player>::iterator it;
		it = std::find_if(_players.begin(), _players.end(), [](Player const& obj) {
			return obj.hlaInstanceHandle == theObject;
		});

		if (it != _players.end()) {
			it->updateAtribiute(theAttributeValues);
		}
		else {
			log("don't find any object in vehicle - reflect atribiute");
		}
	}
	else {
		log("Don't recognize object class in reflected atribiute");
	}
}

/////////////////////////////////////////////////////////////////
//  Implementation methods to handle receive interaction event //
/////////////////////////////////////////////////////////////////
void myHlaFederate::receiveInteractionImpl(
	InteractionClassHandle theInteraction,
	ParameterHandleValueMap const & theParameterValues)
	throw (
		FederateInternalError) {

}

////////////////////////////////////////////////////////////
//  Implementation methods to handle remove object event //
///////////////////////////////////////////////////////////
void myHlaFederate::removeObjectInstanceImpl(
	ObjectInstanceHandle theObject)
	throw (
		FederateInternalError) {

}

////////////////////////////////////////////////////////////////
//  Implementation methods to handle provide Attribute event //
///////////////////////////////////////////////////////////////
void myHlaFederate::provideAttributeValueUpdateImpl(
	ObjectInstanceHandle theObject,
	AttributeHandleSet const & theAttributes)
	throw (
		FederateInternalError) {

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