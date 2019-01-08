#define DLLexport extern "C"  __declspec(dllexport)
#include <iostream>
#include <RTI/RTIambassadorFactory.h>
#include <fstream>
#include <RTI/RTIambassador.h>
#include <Windows.h>
#include "myHlaFederate.h"

using namespace std;

myHlaFederate _myHlaFederate;

DLLexport void Connect() {
	ofstream log;
	log.open("LOG_pluginHLA.txt");
	_myHlaFederate = myHlaFederate(&log);
	
	_myHlaFederate.connect(L"FOM_hla_rts_fps", L"tutorial", L"hla_try", L"unity");
}


