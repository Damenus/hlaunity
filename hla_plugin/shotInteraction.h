#include <RTI/RTIambassador.h>
#include <RTI/encoding/BasicDataElements.h>
#include "AttribiuteType.h"
#include "Debug.h"
#include "dataDll.h"

using namespace std;
using namespace rti1516e;

class shotInteraction
{
public:
	static HLAfloat32LE floatDecoder;
	static InteractionClassHandle shotClassHandle;

	static ParameterHandle shotPosXHandle;
	static ParameterHandle shotPosYHandle;
	static ParameterHandle shotPosZHandle;
	static ParameterHandle hitPosXHandle;
	static ParameterHandle hitPosYHandle;
	static ParameterHandle hitPosZHandle;

	static bool initied;

	static void init(shared_ptr<RTIambassador> _rtiAmbassador);

	void updateParameter(ParameterHandleValueMap const & theParameterValues);
	void getParameterMap(ParameterHandleValueMap* parameterMap);

	void setShotData(ShotData shotData);
	ShotData getShotData();

	shotInteraction();
	shotInteraction(ParameterHandleValueMap const & theParameterValues);
	shotInteraction(ShotData shotData);
	~shotInteraction();

	float shotPosX;
	float shotPosY;
	float shotPosZ;
	float hitPosX;
	float hitPosY;
	float hitPosZ;
};

