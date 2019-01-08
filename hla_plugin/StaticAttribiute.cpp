#include "StaticAttribiute.h"
#include "Player.h"


StaticAttribiute::StaticAttribiute()
{
}

StaticAttribiute::StaticAttribiute(AttributeHandle attribiutrHandle, AttribiutrType type)
{
	this->attribiutrHandle = attribiutrHandle;
	this->type = type;
}

StaticAttribiute::StaticAttribiute(AttributeHandle attribiutrHandle, void* ptrToField, AttribiutrType type)
{
	this->attribiutrHandle = attribiutrHandle;
	this->type = type;
	this->ptrToField = ptrToField;
}

StaticAttribiute::~StaticAttribiute()
{
}
