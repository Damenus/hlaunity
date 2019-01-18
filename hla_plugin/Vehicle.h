#pragma once
#include "SimulationObject.h"
#include "dataDll.h"

using namespace rti1516e;

class Vehicle :
	public SimulationObject
{
public:
	static ObjectClassHandle vehicleClassHandle;
	static bool initiated;
	static void init(shared_ptr<rti1516e::RTIambassador> _rtiAmbassador);
	static void getAttribiuteSet(AttributeHandleSet *attributeSet);

	void updateAttribiutes(AttributeHandleValueMap const & theAttributeValues);
	void getAttribiuteMap(AttributeHandleSet const & theAttributes, AttributeHandleValueMap* attributeMap);
	void getAttribiuteMap(AttributeHandleValueMap* attributeMap);

	Vehicle(ObjectInstanceHandle hlaInstanceHandle);
	~Vehicle();

	void setVehicleData(VehicleData vehicleData);
	VehicleData getVehicleData();
};

