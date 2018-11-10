#include "hlaFederate.h"



hlaFederate::hlaFederate()
{
	mainSquare.PozX = 0;
	mainSquare.PozY = 2;

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
	floatDecoder.decode(theAttributeValues.find(_PosXHandle)->second);
	mainSquare.PozX = floatDecoder.get();
	floatDecoder.decode(theAttributeValues.find(_PosYHandle)->second);
	mainSquare.PozY = floatDecoder.get();
	}

void hlaFederate::setHandle(AttributeHandle posX, AttributeHandle posY) {
	_PosXHandle = posX;
	_PosYHandle = posY;
}

Square hlaFederate::getSquare() {
	return mainSquare;
}