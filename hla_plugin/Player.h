#pragma once
#include "SimulationObject.h"
#include "dataDll.h"

class Player :
	public SimulationObject
{
public:
	static ObjectClassHandle handle;
	static map<AttributeHandle, AttribiuteType> attribiuteStaticCollection;
	static bool initiated;
	static void getAttribiuteSet(AttributeHandleSet *attributeSet);
	static void InitClass(shared_ptr<rti1516e::RTIambassador> _rtiAmbassador);

	Player(ObjectInstanceHandle hlaInstanceHandle, int idSimulation);
	~Player();

	virtual void setValue(AttributeHandle attribiuteHandleToSet, VariableLengthData value);
	virtual VariableLengthData getValue(AttributeHandle attribiuteHandleToGet);

	void setPlayerData(PlayerData playerData);
	PlayerData getPlayerData();
};

