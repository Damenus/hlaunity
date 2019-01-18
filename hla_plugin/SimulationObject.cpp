#include "SimulationObject.h"


HLAfloat32LE SimulationObject::floatDecoder;
int SimulationObject::idCount = 0;

ObjectClassHandle SimulationObject::simulationObjectHandle;

AttributeHandle SimulationObject::posXHandle;
AttributeHandle SimulationObject::posYHandle;
AttributeHandle SimulationObject::posZHandle;

AttributeHandle SimulationObject::rotXHandle;
AttributeHandle SimulationObject::rotZHandle;
AttributeHandle SimulationObject::rotYHandle;

AttributeHandle SimulationObject::velXHandle;
AttributeHandle SimulationObject::velYHandle;
AttributeHandle SimulationObject::velZHandle;

bool SimulationObject::initied=false;

void SimulationObject::init(shared_ptr<rti1516e::RTIambassador> _rtiAmbassador)
{
	Debug::Log("Init SimulationObject");
	simulationObjectHandle=_rtiAmbassador->getObjectClassHandle(L"HLAobjectRoot.SimulationObject");
	posXHandle = _rtiAmbassador->getAttributeHandle(simulationObjectHandle, L"PosX");
	posYHandle = _rtiAmbassador->getAttributeHandle(simulationObjectHandle, L"PosY");
	posZHandle = _rtiAmbassador->getAttributeHandle(simulationObjectHandle, L"PosZ");

	rotXHandle = _rtiAmbassador->getAttributeHandle(simulationObjectHandle, L"RotX");
	rotYHandle = _rtiAmbassador->getAttributeHandle(simulationObjectHandle, L"RotY");
	rotZHandle = _rtiAmbassador->getAttributeHandle(simulationObjectHandle, L"RotZ");

	velXHandle = _rtiAmbassador->getAttributeHandle(simulationObjectHandle, L"RotX");
	velYHandle = _rtiAmbassador->getAttributeHandle(simulationObjectHandle, L"RotY");
	velZHandle = _rtiAmbassador->getAttributeHandle(simulationObjectHandle, L"RotZ");
}

void SimulationObject::getAttribiuteSet(AttributeHandleSet * attributeSet)
{
	Debug::Log("get attribiute set simulation object");
	attributeSet->insert(posXHandle);
	attributeSet->insert(posYHandle);
	attributeSet->insert(posZHandle);

	attributeSet->insert(rotXHandle);
	attributeSet->insert(rotYHandle);
	attributeSet->insert(rotZHandle);

	attributeSet->insert(velXHandle);
	attributeSet->insert(velYHandle);
	attributeSet->insert(velZHandle);
}

SimulationObject::SimulationObject()
{
}

SimulationObject::SimulationObject(ObjectInstanceHandle hlaInstanceHandle)
{
	Debug::Log("Create SimulationObject");
	ID = idCount;
	idCount++;
	this->hlaInstanceHandle = hlaInstanceHandle;
	posX = 0.0;
	posY = 0.0;
	posZ = 0.0;

	rotX = 0.0;
	rotY = 0.0;
	rotZ = 0.0;

	velX = 0.0;
	velY = 0.0;
	velZ = 0.0;
}


SimulationObject::~SimulationObject()
{
}

void SimulationObject::updateAttribiutes(AttributeHandleValueMap const & theAttributeValues)
{
	Debug::Log("update attribiutes SimulationObject");
	AttributeHandleValueMap::const_iterator  itToUpdate = theAttributeValues.find(posXHandle);
	if (itToUpdate != theAttributeValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		posX = floatDecoder.get();
	}
	itToUpdate = theAttributeValues.find(posYHandle);
	if (itToUpdate != theAttributeValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		posY = floatDecoder.get();
	}
	itToUpdate = theAttributeValues.find(posZHandle);
	if (itToUpdate != theAttributeValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		posZ = floatDecoder.get();
	}

	itToUpdate = theAttributeValues.find(rotXHandle);
	if (itToUpdate != theAttributeValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		rotX = floatDecoder.get();
	}
	itToUpdate = theAttributeValues.find(rotYHandle);
	if (itToUpdate != theAttributeValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		rotY = floatDecoder.get();
	}
	itToUpdate = theAttributeValues.find(rotZHandle);
	if (itToUpdate != theAttributeValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		rotZ = floatDecoder.get();
	}

	itToUpdate = theAttributeValues.find(velXHandle);
	if (itToUpdate != theAttributeValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		velX = floatDecoder.get();
	}
	itToUpdate = theAttributeValues.find(velYHandle);
	if (itToUpdate != theAttributeValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		velY = floatDecoder.get();
	}
	itToUpdate = theAttributeValues.find(velZHandle);
	if (itToUpdate != theAttributeValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		velZ = floatDecoder.get();
	}
	//Debug::_log << "Simulation object update attribiutes ID: " << ID << " pozX: " << posX << " pozY: " << posY << " pozZ: " <<posZ << " rotX: " << rotX << " rotY: " <<rotY << " rotZ: " << rotZ << " velZ: " << velZ << " velY: " << velY << " velZ: " << velZ << endl;
}

void SimulationObject::getAttribiuteMap(AttributeHandleSet const & theAttributes, AttributeHandleValueMap * attributeMap)
{
	Debug::Log("get attribiutes SimulationObject");
	AttributeHandleSet::const_iterator  itToProvide = theAttributes.find(posXHandle);
	if (itToProvide != theAttributes.end()) {
		floatDecoder.set(posX);
		attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*itToProvide, floatDecoder.encode()));
	}

	itToProvide = theAttributes.find(posYHandle);
	if (itToProvide != theAttributes.end()) {
		floatDecoder.set(posY);
		attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*itToProvide, floatDecoder.encode()));
	}
	itToProvide = theAttributes.find(posZHandle);
	if (itToProvide != theAttributes.end()) {
		floatDecoder.set(posZ);
		attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*itToProvide, floatDecoder.encode()));
	}

	itToProvide = theAttributes.find(rotXHandle);
	if (itToProvide != theAttributes.end()) {
		floatDecoder.set(rotX);
		attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*itToProvide, floatDecoder.encode()));
	}
	itToProvide = theAttributes.find(rotYHandle);
	if (itToProvide != theAttributes.end()) {
		floatDecoder.set(rotY);
		attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*itToProvide, floatDecoder.encode()));
	}
	itToProvide = theAttributes.find(rotZHandle);
	if (itToProvide != theAttributes.end()) {
		floatDecoder.set(rotZ);
		attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*itToProvide, floatDecoder.encode()));
	}

	itToProvide = theAttributes.find(velXHandle);
	if (itToProvide != theAttributes.end()) {
		floatDecoder.set(velX);
		attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*itToProvide, floatDecoder.encode()));
	}
	itToProvide = theAttributes.find(velYHandle);
	if (itToProvide != theAttributes.end()) {
		floatDecoder.set(velY);
		attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*itToProvide, floatDecoder.encode()));
	}
	itToProvide = theAttributes.find(velZHandle);
	if (itToProvide != theAttributes.end()) {
		floatDecoder.set(velZ);
		attributeMap->insert(pair<AttributeHandle, VariableLengthData>(*itToProvide, floatDecoder.encode()));
	}
}

void SimulationObject::getAttribiuteMap(AttributeHandleValueMap * attributeMap)
{
	Debug::Log("get attribiutes SimulationObject");
	floatDecoder.set(posX);
	attributeMap->insert(pair<AttributeHandle, VariableLengthData>(posXHandle, floatDecoder.encode()));
	floatDecoder.set(posY);
	attributeMap->insert(pair<AttributeHandle, VariableLengthData>(posYHandle, floatDecoder.encode()));
	floatDecoder.set(posZ);
	attributeMap->insert(pair<AttributeHandle, VariableLengthData>(posZHandle, floatDecoder.encode()));

	floatDecoder.set(rotX);
	attributeMap->insert(pair<AttributeHandle, VariableLengthData>(rotXHandle, floatDecoder.encode()));
	floatDecoder.set(rotY);
	attributeMap->insert(pair<AttributeHandle, VariableLengthData>(rotYHandle, floatDecoder.encode()));
	floatDecoder.set(rotZ);
	attributeMap->insert(pair<AttributeHandle, VariableLengthData>(rotZHandle, floatDecoder.encode()));

	floatDecoder.set(velX);
	attributeMap->insert(pair<AttributeHandle, VariableLengthData>(velXHandle, floatDecoder.encode()));
	floatDecoder.set(velY);
	attributeMap->insert(pair<AttributeHandle, VariableLengthData>(velYHandle, floatDecoder.encode()));
	floatDecoder.set(velZ);
	attributeMap->insert(pair<AttributeHandle, VariableLengthData>(velZHandle, floatDecoder.encode()));
}

void SimulationObject::setSimulationObject(SimulationObjectData simulationObjectData)
{
	Debug::Log("set Simulation object data");
	posX = simulationObjectData.posX;
	posY = simulationObjectData.posY;
	posZ = simulationObjectData.posZ;

	rotX = simulationObjectData.rotX;
	rotY = simulationObjectData.rotY;
	rotZ = simulationObjectData.rotZ;

	velX = simulationObjectData.velX;
	velY = simulationObjectData.velY;
	velZ = simulationObjectData.velZ;
}

SimulationObjectData SimulationObject::getSimulationObjectData()
{
	Debug::Log("get Simulation object data");
	SimulationObjectData toReturn;
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




