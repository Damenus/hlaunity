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
	_log << "Enter Publish Player" << endl;
	_log.flush();
	_myHlaFederate.publishPlayer();
}
