#pragma once
enum AttribiutrType
{
	FLOAT
};
#include <RTI/RTIambassador.h>
#include <RTI/encoding/BasicDataElements.h>

using namespace std;
using namespace rti1516e;
class StaticAttribiute
{
public:
	StaticAttribiute();
	StaticAttribiute::StaticAttribiute(AttributeHandle attribiutrHandle, AttribiutrType type);
	StaticAttribiute(AttributeHandle attribiutrHandle, void *ptrToField, AttribiutrType type);
	~StaticAttribiute();

	AttributeHandle attribiutrHandle;
	AttribiutrType type;
	void *ptrToField;
};

