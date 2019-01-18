#pragma once
#include <RTI/RTIambassador.h>
#include <RTI/encoding/BasicDataElements.h>
#include "AttribiuteType.h"
#include "Debug.h"
#include "dataDll.h"

using namespace std;
using namespace rti1516e;



class SimulationObject
{
public:
	static HLAfloat32LE floatDecoder;
	static int idCount;
	static ObjectClassHandle simulationObjectHandle;

	static AttributeHandle posXHandle;
	static AttributeHandle posYHandle;
	static AttributeHandle posZHandle;

	static AttributeHandle rotXHandle;
	static AttributeHandle rotZHandle;
	static AttributeHandle rotYHandle;

	static AttributeHandle velXHandle;
	static AttributeHandle velYHandle;
	static AttributeHandle velZHandle;

	static bool initied;

	static void init(shared_ptr<rti1516e::RTIambassador> _rtiAmbassador);
	static void getAttribiuteSet(AttributeHandleSet *attributeSet);

	SimulationObject();
	SimulationObject(ObjectInstanceHandle hlaInstanceHandle);
	~SimulationObject();

	void updateAttribiutes(AttributeHandleValueMap const & theAttributeValues);
	void getAttribiuteMap(AttributeHandleSet const & theAttributes, AttributeHandleValueMap* attributeMap);
	void getAttribiuteMap(AttributeHandleValueMap* attributeMap);

	void setSimulationObject(SimulationObjectData simulationObjectData);
	SimulationObjectData getSimulationObjectData();

	ObjectInstanceHandle hlaInstanceHandle; //used only to recognize hlaObject
	int ID; // Used only to recognize object in our simulation. It can be diffrent in every simulation

	float posX;
	float posY;
	float posZ;

	float rotX;
	float rotY;
	float rotZ;

	float velX;
	float velY;
	float velZ;

};

