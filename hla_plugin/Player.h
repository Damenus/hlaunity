#pragma once
#include "SimulationObject.h"
class Player :
	public SimulationObject
{
public:
	static ObjectClassHandle playerHandle;
	static AttributeHandle posXHandle;
	static AttributeHandle posYHandle;
	static AttributeHandle posZHandle;
	static AttributeHandle rotXHandle;
	static AttributeHandle rotYHandle;
	static AttributeHandle rotZHandle;
	static AttributeHandle velXHandle;
	static AttributeHandle velYHandle;
	static AttributeHandle velZHandle;

	Player(ObjectInstanceHandle hlaInstanceHandle);
	~Player();
};

