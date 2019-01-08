#include "SimulationObject.h"



SimulationObject::SimulationObject()
{
}

SimulationObject::SimulationObject(ObjectInstanceHandle hlaInstanceHandle)
{
	this->hlaInstanceHandle = hlaInstanceHandle;
	ID = idCount;
	idCount++;
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
	for (AttributeHandleValueMap::const_iterator  itToUpdate = theAttributeValues.begin(); itToUpdate != theAttributeValues.end(); ++itToUpdate)
	{
		setValue(itToUpdate->first, itToUpdate->second);
	}
}

void SimulationObject::getAttribiuteMap(AttributeHandleSet const & theAttributes, AttributeHandleValueMap * attributeMap)
{
	for (AttributeHandleSet::const_iterator toProvide = theAttributes.begin(); toProvide != theAttributes.end(); ++toProvide)
	{
		attributeMap->at(*toProvide) = getValue(*toProvide);
	}
}

void SimulationObject::getAttribiuteMap(AttributeHandleValueMap * attributeMap)
{
	for (map<AttributeHandle, void*>::iterator itLocal = ptrAttribiuteCollection.begin(); itLocal != ptrAttribiuteCollection.end(); ++itLocal) {
		attributeMap->at(itLocal->first) = getValue(itLocal->first);
	}
}

void SimulationObject::setValue(map<AttributeHandle, AttribiutrType> *attribiuteStaticCollection, AttributeHandle attribiuteHandleToSet, VariableLengthData value)
{
	if (attribiuteStaticCollection->find(attribiuteHandleToSet)->second  == AttribiutrType::FLOAT) {
		floatDecoder.decode(value);
		*((float*)ptrAttribiuteCollection.find(attribiuteHandleToSet)->second) = floatDecoder.get();
	}
	else {

	}
}

VariableLengthData SimulationObject::getValue(map<AttributeHandle, AttribiutrType> *attribiuteStaticCollection, AttributeHandle attribiuteHandleToGet)
{
	if (attribiuteStaticCollection->find(attribiuteHandleToGet)->second == AttribiutrType::FLOAT) {
		floatDecoder.set(*((float*)ptrAttribiuteCollection.find(attribiuteHandleToGet)->second));
		return floatDecoder.encode();
	}
	else {

	}
}





