#include "SimulationObject.h"



SimulationObject::SimulationObject(ObjectInstanceHandle hlaInstanceHandle)
{
	this->hlaInstanceHandle = hlaInstanceHandle;
	ID = idCount;
	idCount++;
	position.setXYZ(0, 0, 0);
	rotation.setXYZ(0, 0, 0);
	velocity.setXYZ(0, 0, 0);
}


SimulationObject::~SimulationObject()
{
}



