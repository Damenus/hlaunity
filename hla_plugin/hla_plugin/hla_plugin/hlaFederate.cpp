#include "hlaFederate.h"



hlaFederate::hlaFederate()
{
	mainSquare.PozX = 0;
	mainSquare.PozY = 0;
}


hlaFederate::~hlaFederate()
{
}

void hlaFederate::reflectAttributeValues(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	SupplementalReflectInfo theReflectInfo)
	throw (FederateInternalError) {
	reflectAttributeValues(theObject, theAttributeValues);
}

void hlaFederate::reflectAttributeValues(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	SupplementalReflectInfo theReflectInfo)
	throw (FederateInternalError) {
	reflectAttributeValues(theObject, theAttributeValues);
}

void hlaFederate::reflectAttributeValues(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues,
	VariableLengthData const & theUserSuppliedTag,
	OrderType sentOrder,
	TransportationType theType,
	LogicalTime const & theTime,
	OrderType receivedOrder,
	MessageRetractionHandle theHandle,
	SupplementalReflectInfo theReflectInfo)
	throw (FederateInternalError) {
	reflectAttributeValues(theObject, theAttributeValues);
}

void hlaFederate::reflectAttributeValues(
	ObjectInstanceHandle theObject,
	AttributeHandleValueMap const & theAttributeValues)
	throw (FederateInternalError) {
	HLAfloatDecoder.decode(theAttributeValues.find(PosXAttributeHandle)->second);
	mainSquare.PozX = HLAfloatDecoder.get();
	HLAfloatDecoder.decode(theAttributeValues.find(PosYAttributeHandle)->second);
	mainSquare.PozY = HLAfloatDecoder.get();
}

square hlaFederate::getSquare() {
	return mainSquare;
}

void hlaFederate::setAtributeHandle(AttributeHandle PosX, AttributeHandle PosY) {
	this->PosXAttributeHandle = PosX;
	this->PosYAttributeHandle = PosY;
}