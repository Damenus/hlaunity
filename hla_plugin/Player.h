#pragma once
#include "SimulationObject.h"
#include "dataDll.h"
#include "StaticAttribiute.h"

class Player :
	public SimulationObject
{
public:
	static ObjectClassHandle handle;
	static map<AttributeHandle,AttribiutrType> attribiuteStaticCollection;
	static void getAttribiuteSet(AttributeHandleSet *attributeSet);
	static void InitClass(auto_ptr<rti1516e::RTIambassador> _rtiAmbassador);

	Player(ObjectInstanceHandle hlaInstanceHandle);
	~Player();

	void setValue(AttributeHandle attribiuteHandleToSet, VariableLengthData value);
	VariableLengthData getValue(AttributeHandle attribiuteHandleToGet);

	void setPlayerData(PlayerData playerData);
	PlayerData getPlayerData();
};

