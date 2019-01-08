#include "Vehicle.h"


void Vehicle::getAttribiuteSet(AttributeHandleSet  *attributeSet)
{
	for (map<AttributeHandle, AttribiutrType>::iterator itLocal = attribiuteStaticCollection.begin(); itLocal != attribiuteStaticCollection.end(); ++itLocal) {
		attributeSet->insert(itLocal->first);
	}
}

void Vehicle::InitClass(auto_ptr<rti1516e::RTIambassador> _rtiAmbassador)
{
	handle = _rtiAmbassador->getObjectClassHandle(L"Player");


	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"PosX")] = AttribiutrType::FLOAT;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"PosY")] = AttribiutrType::FLOAT;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"PosZ")] = AttribiutrType::FLOAT;

	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"RotX")] = AttribiutrType::FLOAT;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"RotY")] = AttribiutrType::FLOAT;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"RotZ")] = AttribiutrType::FLOAT;

	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"VelX")] = AttribiutrType::FLOAT;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"VelY")] = AttribiutrType::FLOAT;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"VelZ")] = AttribiutrType::FLOAT;

}

Vehicle::Vehicle(ObjectInstanceHandle hlaInstanceHandle)
{
	map<AttributeHandle, AttribiutrType>::iterator it;
	it = attribiuteStaticCollection.begin();

	ptrAttribiuteCollection[it->first] = &posX;
	it++;
	ptrAttribiuteCollection[it->first] = &posY;
	it++;
	ptrAttribiuteCollection[it->first] = &posZ;
	it++;

	ptrAttribiuteCollection[it->first] = &rotX;
	it++;
	ptrAttribiuteCollection[it->first] = &rotY;
	it++;
	ptrAttribiuteCollection[it->first] = &rotZ;
	it++;

	ptrAttribiuteCollection[it->first] = &velX;
	it++;
	ptrAttribiuteCollection[it->first] = &velY;
	it++;
	ptrAttribiuteCollection[it->first] = &velZ;

	SimulationObject::SimulationObject(hlaInstanceHandle);
}


Vehicle::~Vehicle()
{
}
void Vehicle::setValue(AttributeHandle attribiuteHandleToSet, VariableLengthData value)
{
	SimulationObject::setValue(&attribiuteStaticCollection, attribiuteHandleToSet, value);
}

VariableLengthData Vehicle::getValue(AttributeHandle attribiuteHandleToGet)
{
	return SimulationObject::getValue(&attribiuteStaticCollection, attribiuteHandleToGet);
}

void Vehicle::setVehicleData(VehicleData vehicleData)
{
	posX = vehicleData.posX;
	posY = vehicleData.posY;
	posZ = vehicleData.posZ;

	rotX = vehicleData.rotX;
	rotY = vehicleData.rotY;
	rotZ = vehicleData.rotZ;

	velX = vehicleData.velX;
	velY = vehicleData.velY;
	velZ = vehicleData.velZ;
}

VehicleData Vehicle::getVehicleData()
{
	VehicleData toReturn;

	toReturn.ID = ID;

	toReturn.posX = posX;
	toReturn.posY = posY;
	toReturn.posZ = posZ;

	toReturn.rotX = rotX;
	toReturn.rotY = rotY;
	toReturn.rotZ = rotZ;

	toReturn.velX = velX;
	toReturn.velY = velY;
	toReturn.velZ = velZ;

	return toReturn;
}
