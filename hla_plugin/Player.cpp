#include "Player.h"

ObjectClassHandle Player::playerClassHandle;
bool Player::initiated = false;

void Player::init(shared_ptr<rti1516e::RTIambassador> _rtiAmbassador)
{
	Debug::Log("Init Player");
	if (!SimulationObject::initied) {
		SimulationObject::init(_rtiAmbassador);
	}
	playerClassHandle = _rtiAmbassador->getObjectClassHandle(L"HLAobjectRoot.SimulationObject.Player");
	initiated = true;
}

void Player::getAttribiuteSet(AttributeHandleSet * attributeSet)
{
	Debug::Log("get attribiute set player");
	SimulationObject::getAttribiuteSet(attributeSet);
}

Player::Player(ObjectInstanceHandle hlaInstanceHandle) : SimulationObject(hlaInstanceHandle)
{
	Debug::Log("create instance player");

}

Player::~Player()
{}

void Player::updateAttribiutes(AttributeHandleValueMap const & theAttributeValues)
{
	Debug::Log("update attribiutes player");
	SimulationObject::updateAttribiutes(theAttributeValues);
}

void Player::getAttribiuteMap(AttributeHandleSet const & theAttributes, AttributeHandleValueMap * attributeMap)
{
	Debug::Log("get attribiutes player");
	SimulationObject::getAttribiuteMap(theAttributes, attributeMap);
}

void Player::getAttribiuteMap(AttributeHandleValueMap * attributeMap)
{
	Debug::Log("get attribiutes player");
	SimulationObject::getAttribiuteMap(attributeMap);
}

void Player::setPlayerData(PlayerData playerData)
{
	Debug::Log("set player Data");
	SimulationObjectData simulationObjectData;

	simulationObjectData.posX = playerData.posX;
	simulationObjectData.posY = playerData.posY;
	simulationObjectData.posZ = playerData.posZ;

	simulationObjectData.rotX = playerData.rotX;
	simulationObjectData.rotY = playerData.rotY;
	simulationObjectData.rotZ=playerData.rotZ;

	simulationObjectData.velX = playerData.velX;
	simulationObjectData.velY = playerData.velY;
	simulationObjectData.velZ= playerData.velZ;
	SimulationObject::setSimulationObject(simulationObjectData);

	Debug::_log << "player: ID: " << ID << " pozX: " << posX << " pozY: " << posY << " pozZ: " << posZ << " rotX: " << rotX << " rotY: " << rotY << " rotZ: " << rotZ << " velZ: " << velZ << " velY: " << velY << " velZ: " << velZ << endl;
}

PlayerData Player::getPlayerData()
{
	Debug::Log("get player Data");
	PlayerData toReturn;
	SimulationObjectData simulationObjectData = SimulationObject::getSimulationObjectData();

	toReturn.ID = simulationObjectData.ID;

	toReturn.posX = simulationObjectData.posX;
	toReturn.posY = simulationObjectData.posY;
	toReturn.posZ = simulationObjectData.posZ;

	toReturn.rotX = simulationObjectData.rotX;
	toReturn.rotY = simulationObjectData.rotY;
	toReturn.rotZ = simulationObjectData.rotZ;

	toReturn.velX = simulationObjectData.velX;
	toReturn.velY = simulationObjectData.velY;
	toReturn.velZ = simulationObjectData.velZ;

	return toReturn;
}
