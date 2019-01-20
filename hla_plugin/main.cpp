#define DLLexport extern "C"  __declspec(dllexport)
#include <RTI/RTIambassadorFactory.h>
#include <RTI/RTIambassador.h>
#include <Windows.h>
#include "myHlaFederate.h"
#include "Debug.h"
using namespace std;

myHlaFederate _myHlaFederate;

DLLexport void Connect() {

	Debug::init("LOG_pluginHLA.txt");
	_myHlaFederate = myHlaFederate();
	
	_myHlaFederate.connect(L"FOM_hla_rts_fps.xml", L"tutorial", L"hla_try", L"unity");
}
DLLexport void Disconnect() {
	Debug::close();
	_myHlaFederate.disconnect();
}

DLLexport void SubscribeVehicle() {
	_myHlaFederate.subscribeVehicle();
}
DLLexport void SubscribePlayer() {
	_myHlaFederate.subscribePlayer();
}
DLLexport void SubscribeShot() {
	_myHlaFederate.subscribeShot();
}
DLLexport void PublishVehicle() {
	_myHlaFederate.publishVehicle();
}
DLLexport void PublishPlayer() {
	_myHlaFederate.publishPlayer();
}
DLLexport void PublishShot() {
	_myHlaFederate.publishShot();
}
DLLexport int CreateVehicle() {
	return _myHlaFederate.createVehicle();
}
DLLexport int CreatePlayer() {
	return _myHlaFederate.createPlayer();
}

DLLexport void UpdateVehicle(VehicleData vehicleData) {
	_myHlaFederate.updateVehicle(vehicleData);
}
DLLexport void UpdatePlayer(PlayerData playerData) {
	Debug::_log<< "update playerData: ID" << playerData.ID << " pozX: " << playerData.posX << " pozY: " << playerData.posY << " pozZ: " << playerData.posZ << " rotX: " << playerData.rotX << " rotY: " << playerData.rotY << " rotZ: " << playerData.rotZ << " velZ: " << playerData.velZ << " velY: " << playerData.velY << " velZ: "<< playerData.velZ<<endl;
	_myHlaFederate.updatePlayer(playerData);	
}

DLLexport VehicleData* GetVehicles(int &size) {
	vector<Vehicle> data = _myHlaFederate.getVehicles();
	size = data.size();
	VehicleData *dataToReturn = (VehicleData*)CoTaskMemAlloc(sizeof(VehicleData) * size);

	for (int i=0;i<size;i++)
	{
		dataToReturn[i] = data[i].getVehicleData();
		Debug::_log << "Get vehicles main: ID: " << dataToReturn[i].ID << " pozX: " << dataToReturn[i].posX << " pozY: " << dataToReturn[i].posY << " pozZ: " << dataToReturn[i].posZ << " rotX: " << dataToReturn[i].rotX << " rotY: " << dataToReturn[i].rotY << " rotZ: " << dataToReturn[i].rotZ << " velZ: " << dataToReturn[i].velZ << " velY: " << dataToReturn[i].velY << " velZ: " << dataToReturn[i].velZ << endl;
	}
	return dataToReturn;
}
DLLexport PlayerData* GetPlayers(int &size) {
	vector<Player> data = _myHlaFederate.getPlayers();
	size = data.size();
	PlayerData *dataToReturn = (PlayerData*)CoTaskMemAlloc(sizeof(PlayerData) * size);

	for (int i = 0; i<size; i++)
	{
		dataToReturn[i] = data[i].getPlayerData();
	}
	return dataToReturn;
}

DLLexport void SendShot(ShotData shotData) {
	_myHlaFederate.sentShot(shotData);
}
DLLexport ShotData* GetShots(int &size) {
	vector<shotInteraction> data = _myHlaFederate.getShots();
	size = data.size();
	ShotData *dataToReturn = (ShotData*)CoTaskMemAlloc(sizeof(ShotData) * size);

	for (int i = 0; i<size; i++)
	{
		dataToReturn[i] = data[i].getShotData();
	}
	return dataToReturn;
}