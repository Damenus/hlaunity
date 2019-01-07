#include "Dim3.h"



Dim3::Dim3()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Dim3::Dim3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Dim3::~Dim3()
{
}

void Dim3::setXYZ(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
