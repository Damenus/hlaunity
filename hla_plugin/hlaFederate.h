#include <RTI\NullFederateAmbassador.h>
#include <RTI/encoding/BasicDataElements.h>
//#include "Square.h"
#include "hlaPlugin.h"
#include <RTI/encoding/HLAfixedRecord.h>

using namespace std;
using namespace rti1516e;

class hlaFederate : public NullFederateAmbassador
{
public:
	Square mainSquare;
	ObjectInstanceHandle _mainSqare;
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
	 void setSquareX(float x);
	 void setSquareY(float y);

	 rti1516e::VariableLengthData encode();
	 rti1516e::VariableLengthData encodeX();
	 rti1516e::VariableLengthData encodeY();
};

