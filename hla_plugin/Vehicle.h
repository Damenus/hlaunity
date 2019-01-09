#pragma once
#include "SimulationObject.h"
#include "dataDll.h"

using namespace rti1516e;

class Vehicle :
	public SimulationObject
{
public:
	static ObjectClassHandle handle;
	static map<AttributeHandle, AttribiuteType> attribiuteStaticCollection;
	static bool initiated;
	static void getAttribiuteSet(AttributeHandleSet *attributeSet);
	static void InitClass(shared_ptr<rti1516e::RTIambassador> _rtiAmbassador);
	

	Vehicle(ObjectInstanceHandle hlaInstanceHandle);
	~Vehicle();

	void setValue(AttributeHandle attribiuteHandleToSet, VariableLengthData value);
	VariableLengthData getValue(AttributeHandle attribiuteHandleToGet);

	void setVehicleData(VehicleData vehicleData);
	VehicleData getVehicleData();
};

