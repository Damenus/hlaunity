#pragma once
#include <RTI/RTIambassador.h>
#include <RTI/encoding/BasicDataElements.h>
#include "AttribiuteType.h"

using namespace std;
using namespace rti1516e;



class SimulationObject
{
public:
	static int idCount;
	static HLAfloat32BE floatDecoder;

	SimulationObject();
	SimulationObject(ObjectInstanceHandle hlaInstanceHandle);
	~SimulationObject();

	map<AttributeHandle, void*> ptrAttribiuteCollection;

	void updateAttribiutes(AttributeHandleValueMap const & theAttributeValues);
	void getAttribiuteMap(AttributeHandleSet const & theAttributes, AttributeHandleValueMap* attributeMap);
	void getAttribiuteMap(AttributeHandleValueMap* attributeMap);

	void setValue(map<AttributeHandle, AttribiuteType> *attribiuteStaticCollection,AttributeHandle attribiuteHandleToSet, VariableLengthData value);
	VariableLengthData getValue(map<AttributeHandle, AttribiuteType> *attribiuteStaticCollection,AttributeHandle attribiuteHandleToGet);
	
	virtual void setValue(AttributeHandle attribiuteHandleToSet, VariableLengthData value) {};
	virtual VariableLengthData getValue(AttributeHandle attribiuteHandleToGet) { return VariableLengthData(); };

	// faster to write then use setter getter

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

