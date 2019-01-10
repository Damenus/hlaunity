#define DLLexport extern "C"  __declspec(dllexport)
#include <iostream>
#include <RTI/RTIambassadorFactory.h>
#include <fstream>
#include <RTI/RTIambassador.h>
#include <Windows.h>
#include "myHlaFederate.h"

using namespace std;

myHlaFederate _myHlaFederate;
ofstream _log;

DLLexport void Connect() {

	_log.open("LOG_pluginHLA.txt");
	_myHlaFederate = myHlaFederate(&_log);
	
	_myHlaFederate.connect(L"FOM_hla_rts_fps.xml", L"tutorial", L"hla_try", L"unity");
}
DLLexport void Disconnect() {

	_myHlaFederate.disconnect();
}

DLLexport void SubscribeVehicle() {
	_myHlaFederate.subscribeVehicle();
}
DLLexport void SubscribePlayer() {
	_myHlaFederate.subscribePlayer();
}
DLLexport void PublishVehicle() {
	_myHlaFederate.publishVehicle();
}
DLLexport void PublishPlayer() {
	_myHlaFederate.publishPlayer();
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
	_myHlaFederate.updatePlayer(playerData);	
}

DLLexport VehicleData* GetVehicles(int &size) {
	vector<Vehicle> data = _myHlaFederate.getVehicles();
	size = data.size();
	VehicleData *dataToReturn = (VehicleData*)CoTaskMemAlloc(sizeof(VehicleData) * size);

	for (int i=0;i<size;i++)
	{
		dataToReturn[i] = data[i].getVehicleData();
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