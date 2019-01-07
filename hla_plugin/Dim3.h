#pragma once
class Dim3
{
public:
	float x;
	float y;
	float z;

	Dim3();
	Dim3(float x, float y, float z);
	~Dim3();

	void setXYZ(float x, float y, float z);
};

