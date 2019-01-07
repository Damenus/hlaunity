#pragma once
#include "Dim3.h"
#include <RTI/RTIambassador.h>
#include <RTI/encoding/BasicDataElements.h>

using namespace std;
using namespace rti1516e;

class SimulationObject
{
public:
	static int idCount;
	SimulationObject::SimulationObject(ObjectInstanceHandle hlaInstanceHandle);
	~SimulationObject();

	// faster to write then use setter getter

	ObjectInstanceHandle hlaInstanceHandle; //used only to recognize hlaObject
	int ID; // Used only to recognize object in our simulation. It can be diffrent in every simulation


	Dim3 position;
	Dim3 rotation;
	Dim3 velocity;
};

