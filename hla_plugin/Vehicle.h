#pragma once
#include "SimulationObject.h"


using namespace rti1516e;

class Vehicle :
	public SimulationObject
{
public:
	 static ObjectClassHandle vehicleHandle;
	 static AttributeHandle posXHandle;
	 static AttributeHandle posYHandle;
	 static AttributeHandle posZHandle;
	 static AttributeHandle rotXHandle;
	 static AttributeHandle rotYHandle;
	 static AttributeHandle rotZHandle;
	 static AttributeHandle velXHandle;
	 static AttributeHandle velYHandle;
	 static AttributeHandle velZHandle;

	Vehicle(ObjectInstanceHandle hlaInstanceHandle);
	~Vehicle();
};

