#pragma once
#ifdef HLAPLUGIN_EXPORTS
#define HLAPLUGIN_API __declspec(dllexport)
#else
#define HLAPLUGIN_API __declspec(dllimport)
#endif

struct HLAPLUGIN_API VehicleData {
	int ID;
	float posX;
	float posY;
	float posZ;
	float rotX;
	float rotY;
	float rotZ;
	float velX;
	float velY;
	float velZ;
};

struct HLAPLUGIN_API PlayerData {
	int ID;
	float posX;
	float posY;
	float posZ;
	float rotX;
	float rotY;
	float rotZ;
	float velX;
	float velY;
	float velZ;
};

struct HLAPLUGIN_API SimulationObjectData {
	int ID;
	float posX;
	float posY;
	float posZ;
	float rotX;
	float rotY;
	float rotZ;
	float velX;
	float velY;
	float velZ;
};