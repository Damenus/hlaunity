#include <RTI/NullFederateAmbassador.h>
#include <RTI/encoding/BasicDataElements.h>
#include "square.h"

using namespace  rti1516e;



class hlaFederate : public NullFederateAmbassador
{
public:
	hlaFederate();
	~hlaFederate();

	virtual void reflectAttributeValues(
		ObjectInstanceHandle theObject,
		AttributeHandleValueMap const & theAttributeValues,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		TransportationType theType,
		SupplementalReflectInfo theReflectInfo)
		throw (FederateInternalError);

	virtual void reflectAttributeValues(
		ObjectInstanceHandle theObject,
		AttributeHandleValueMap const & theAttributeValues,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		TransportationType theType,
		LogicalTime const & theTime,
		OrderType receivedOrder,
		SupplementalReflectInfo theReflectInfo)
		throw (FederateInternalError);

	  virtual void reflectAttributeValues(
		  ObjectInstanceHandle theObject,
		  AttributeHandleValueMap const & theAttributeValues,
		  VariableLengthData const & theUserSuppliedTag,
		  OrderType sentOrder,
		  TransportationType theType,
		  LogicalTime const & theTime,
		  OrderType receivedOrder,
		  MessageRetractionHandle theHandle,
		  SupplementalReflectInfo theReflectInfo)
		  throw (FederateInternalError);

	  virtual void reflectAttributeValues(
		  ObjectInstanceHandle theObject,
		  AttributeHandleValueMap const & theAttributeValues)
		  throw (FederateInternalError);

	square getSquare() throw (rti1516e::Exception);
	
	void setAtributeHandle(AttributeHandle PosX, AttributeHandle PosY) throw (rti1516e::Exception);

	private:
		square mainSquare;
		AttributeHandle  PosXAttributeHandle;
		AttributeHandle  PosYAttributeHandle;
		HLAfloat32BE HLAfloatDecoder;
};

