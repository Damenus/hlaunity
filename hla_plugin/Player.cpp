#include "Player.h"

ObjectClassHandle Player::handle;
map<AttributeHandle, AttribiuteType> Player::attribiuteStaticCollection;
bool Player::initiated = false;

void Player::getAttribiuteSet(AttributeHandleSet *attributeSet)
{
	for (map<AttributeHandle, AttribiuteType>::iterator itLocal = attribiuteStaticCollection.begin(); itLocal != attribiuteStaticCollection.end(); ++itLocal) {
		attributeSet->insert(itLocal->first);
	}
}

void Player::InitClass(shared_ptr<rti1516e::RTIambassador> _rtiAmbassador)
{
	handle = _rtiAmbassador->getObjectClassHandle(L"HLAobjectRoot.SimulationObject.Player");


	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle,L"PosX")] = AttribiuteType::FLOAT_HLA;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"PosY")] = AttribiuteType::FLOAT_HLA;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"PosZ")] = AttribiuteType::FLOAT_HLA;

	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"RotX")] = AttribiuteType::FLOAT_HLA;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"RotY")] = AttribiuteType::FLOAT_HLA;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"RotZ")] = AttribiuteType::FLOAT_HLA;

	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"VelX")] = AttribiuteType::FLOAT_HLA;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"VelY")] = AttribiuteType::FLOAT_HLA;
	attribiuteStaticCollection[_rtiAmbassador->getAttributeHandle(handle, L"VelZ")] = AttribiuteType::FLOAT_HLA;

	initiated = true;
}

Player::Player(ObjectInstanceHandle hlaInstanceHandle, int idSimulation) : SimulationObject(hlaInstanceHandle,idSimulation)
{
	map<AttributeHandle, AttribiuteType>::iterator it;
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
	SimulationObject::SimulationObject(hlaInstanceHandle, idSimulation);
}


Player::~Player()
{
}

void Player::setValue(AttributeHandle attribiuteHandleToSet, VariableLengthData value)
{
	SimulationObject::setValue(&attribiuteStaticCollection, attribiuteHandleToSet, value);
}

VariableLengthData Player::getValue(AttributeHandle attribiuteHandleToGet)
{
	return SimulationObject::getValue(&attribiuteStaticCollection, attribiuteHandleToGet);
}

void Player::setPlayerData(PlayerData playerData)
{
	posX = playerData.posX;
	posY = playerData.posY; 
	posZ = playerData.posZ;

	rotX = playerData.rotX; 
	rotY = playerData.rotY; 
	rotZ=playerData.rotZ;

	velX = playerData.velX;
	velY = playerData.velY;
	velZ= playerData.velZ;
}

PlayerData Player::getPlayerData()
{
	PlayerData toReturn;

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
