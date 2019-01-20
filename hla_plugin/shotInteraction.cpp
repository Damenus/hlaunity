#include "shotInteraction.h"

HLAfloat32LE shotInteraction::floatDecoder;
InteractionClassHandle shotInteraction::shotClassHandle;

ParameterHandle shotInteraction::shotPosXHandle;
ParameterHandle shotInteraction::shotPosYHandle;
ParameterHandle shotInteraction::shotPosZHandle;
ParameterHandle shotInteraction::hitPosXHandle;
ParameterHandle shotInteraction::hitPosYHandle;
ParameterHandle shotInteraction::hitPosZHandle;

bool shotInteraction::initied = false;

void shotInteraction::init(shared_ptr<RTIambassador> _rtiAmbassador)
{
	Debug::Log("Init shot interaction");
	shotClassHandle = _rtiAmbassador->getInteractionClassHandle(L"HLAinteractionRoot.Shot");

	shotPosXHandle = _rtiAmbassador->getParameterHandle(shotClassHandle, L"ShotPosX");
	shotPosYHandle = _rtiAmbassador->getParameterHandle(shotClassHandle, L"ShotPosY");
	shotPosZHandle = _rtiAmbassador->getParameterHandle(shotClassHandle, L"ShotPosZ");

	hitPosXHandle = _rtiAmbassador->getParameterHandle(shotClassHandle, L"HitPosX");
	hitPosYHandle = _rtiAmbassador->getParameterHandle(shotClassHandle, L"HitPosY");
	hitPosZHandle = _rtiAmbassador->getParameterHandle(shotClassHandle, L"HitPosZ");

	initied = true;
}

void shotInteraction::updateParameter(ParameterHandleValueMap const & theParameterValues)
{
	Debug::Log("update parametr shot interaction");
	ParameterHandleValueMap::const_iterator  itToUpdate = theParameterValues.find(shotPosXHandle);
	if (itToUpdate != theParameterValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		shotPosX = floatDecoder.get();
	}
	itToUpdate = theParameterValues.find(shotPosYHandle);
	if (itToUpdate != theParameterValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		shotPosY = floatDecoder.get();
	}
	itToUpdate = theParameterValues.find(shotPosZHandle);
	if (itToUpdate != theParameterValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		shotPosZ = floatDecoder.get();
	}

	itToUpdate = theParameterValues.find(hitPosXHandle);
	if (itToUpdate != theParameterValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		hitPosX = floatDecoder.get();
	}
	itToUpdate = theParameterValues.find(hitPosYHandle);
	if (itToUpdate != theParameterValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		hitPosY = floatDecoder.get();
	}
	itToUpdate = theParameterValues.find(hitPosZHandle);
	if (itToUpdate != theParameterValues.end()) {
		floatDecoder.decode(itToUpdate->second);
		hitPosZ = floatDecoder.get();
	}
}

void shotInteraction::getParameterMap(ParameterHandleValueMap * parameterMap)
{
	Debug::Log("get parametr set shot interaction");

	floatDecoder.set(shotPosX);
	parameterMap->insert(pair<ParameterHandle, VariableLengthData>(shotPosXHandle, floatDecoder.encode()));
	floatDecoder.set(shotPosY);
	parameterMap->insert(pair<ParameterHandle, VariableLengthData>(shotPosYHandle, floatDecoder.encode()));
	floatDecoder.set(shotPosZ);
	parameterMap->insert(pair<ParameterHandle, VariableLengthData>(shotPosZHandle, floatDecoder.encode()));

	floatDecoder.set(hitPosX);
	parameterMap->insert(pair<ParameterHandle, VariableLengthData>(hitPosXHandle, floatDecoder.encode()));
	floatDecoder.set(hitPosY);
	parameterMap->insert(pair<ParameterHandle, VariableLengthData>(hitPosYHandle, floatDecoder.encode()));
	floatDecoder.set(hitPosZ);
	parameterMap->insert(pair<ParameterHandle, VariableLengthData>(hitPosZHandle, floatDecoder.encode()));
}

void shotInteraction::setShotData(ShotData shotData)
{
	Debug::Log("set shot data");
}

ShotData shotInteraction::getShotData()
{
	Debug::Log("get shot data");
	ShotData toReturn;

	toReturn.shotPosX = shotPosX;
	toReturn.shotPosY = shotPosY;
	toReturn.shotPosZ = shotPosZ;

	toReturn.hitPosX = hitPosX;
	toReturn.hitPosY = hitPosY;
	toReturn.hitPosZ = hitPosZ;

	return toReturn;
}

shotInteraction::shotInteraction()
{
	Debug::Log("Create Shot interaction");
}

shotInteraction::shotInteraction(ParameterHandleValueMap const & theParameterValues)
{
	updateParameter(theParameterValues);
}

shotInteraction::shotInteraction(ShotData shotData)
{
	setShotData(shotData);
}


shotInteraction::~shotInteraction()
{
}
