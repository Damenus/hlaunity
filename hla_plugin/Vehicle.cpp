#include "Vehicle.h"

ObjectClassHandle Vehicle::vehicleClassHandle;
bool Vehicle::initiated=false;

void Vehicle::init(shared_ptr<rti1516e::RTIambassador> _rtiAmbassador)
{
	Debug::Log("Init Vehicle");
	if (!SimulationObject::initied) {
		SimulationObject::init(_rtiAmbassador);
	}
	vehicleClassHandle = _rtiAmbassador->getObjectClassHandle(L"HLAobjectRoot.SimulationObject.Vehicle");
	initiated = true;
}
Vehicle::Vehicle(ObjectInstanceHandle hlaInstanceHandle) :SimulationObject(hlaInstanceHandle)
{
	Debug::Log("create instance Vehicle");
}

Vehicle::~Vehicle()
{
}
void Vehicle::getAttribiuteSet(AttributeHandleSet  *attributeSet)
{
	Debug::Log("get attribiute set Vehicle");
	SimulationObject::getAttribiuteSet(attributeSet);
}

void Vehicle::updateAttribiutes(AttributeHandleValueMap const & theAttributeValues)
{
	Debug::Log("update attribiutes Vehicle");
	SimulationObject::updateAttribiutes(theAttributeValues);
}

void Vehicle::getAttribiuteMap(AttributeHandleSet const & theAttributes, AttributeHandleValueMap * attributeMap)
{
	Debug::Log("get attribiutes Vehicle");
	SimulationObject::getAttribiuteMap(theAttributes, attributeMap);
}

void Vehicle::getAttribiuteMap(AttributeHandleValueMap * attributeMap)
{
	Debug::Log("get attribiutes Vehicle");
	SimulationObject::getAttribiuteMap(attributeMap);
}

void Vehicle::setVehicleData(VehicleData vehicleData)
{
	Debug::Log("set vehicle Data");
	SimulationObjectData simulationObjectData;

	simulationObjectData.posX = vehicleData.posX;
	simulationObjectData.posY = vehicleData.posY;
	simulationObjectData.posZ = vehicleData.posZ;

	simulationObjectData.rotX = vehicleData.rotX;
	simulationObjectData.rotY = vehicleData.rotY;
	simulationObjectData.rotZ = vehicleData.rotZ;

	simulationObjectData.velX = vehicleData.velX;
	simulationObjectData.velY = vehicleData.velY;
	simulationObjectData.velZ = vehicleData.velZ;
	SimulationObject::setSimulationObject(simulationObjectData);

	Debug::_log << "vehicle: ID: " << ID << " pozX: " << posX << " pozY: " << posY << " pozZ: " << posZ << " rotX: " << rotX << " rotY: " << rotY << " rotZ: " << rotZ << " velZ: " << velZ << " velY: " << velY << " velZ: " << velZ << endl;
}

VehicleData Vehicle::getVehicleData()
{
	Debug::Log("get vehicle Data");
	VehicleData toReturn;
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
