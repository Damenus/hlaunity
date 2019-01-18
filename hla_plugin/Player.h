#pragma once
#include "SimulationObject.h"
#include "dataDll.h"
#include "Debug.h"

class Player :
	public SimulationObject
{
public:
	static ObjectClassHandle playerClassHandle;
	static bool initiated;
	static void init(shared_ptr<rti1516e::RTIambassador> _rtiAmbassador);
	static void getAttribiuteSet(AttributeHandleSet *attributeSet);

	void updateAttribiutes(AttributeHandleValueMap const & theAttributeValues);
	void getAttribiuteMap(AttributeHandleSet const & theAttributes, AttributeHandleValueMap* attributeMap);
	void getAttribiuteMap(AttributeHandleValueMap* attributeMap);

	Player(ObjectInstanceHandle hlaInstanceHandle);
	~Player();

	void setPlayerData(PlayerData playerData);
	PlayerData getPlayerData();
};

