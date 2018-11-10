#include <RTI\NullFederateAmbassador.h>
#include <RTI/encoding/BasicDataElements.h>
#include "Square.h"

using namespace std;
using namespace rti1516e;

class hlaFederate : public NullFederateAmbassador
{
public:
	Square mainSquare;
	AttributeHandle   _PosXHandle;
	AttributeHandle    _PosYHandle;
	HLAfloat32BE	floatDecoder;

	hlaFederate();

	void reflectAttributeValues(
		ObjectInstanceHandle theObject,
		AttributeHandleValueMap const & theAttributeValues,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		TransportationType theType,
		SupplementalReflectInfo theReflectInfo)
		throw (
			FederateInternalError);

	 void reflectAttributeValues(
		 ObjectInstanceHandle theObject,
		 AttributeHandleValueMap const & theAttributeValues,
		 VariableLengthData const & theUserSuppliedTag,
		 OrderType sentOrder,
		 TransportationType theType,
		 LogicalTime const & theTime,
		 OrderType receivedOrder,
		 SupplementalReflectInfo theReflectInfo)
		 throw (
			 FederateInternalError);

	 void reflectAttributeValues(
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
			 FederateInternalError);
	 void reflectAttributeValues(
		 ObjectInstanceHandle theObject,
		 AttributeHandleValueMap const & theAttributeValues)
		 throw (
			 FederateInternalError);
	 void setHandle(AttributeHandle posX, AttributeHandle posY);

	 Square getSquare();
};

