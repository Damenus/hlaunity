#define DLLexport extern "C"  __declspec(dllexport)
#include <iostream>
#include <RTI/RTIambassadorFactory.h>
#include <fstream>
#include "hlaFederate.h"
#include <RTI/RTIambassador.h>
#include <Windows.h>

using namespace std;
using namespace rti1516e;

auto_ptr<RTIambassador> _rtiAmbassador;
wstring FOM = L"Square.xml",localSetting= L"tutorial", federationName=L"Square try", federateName = L"Unity plugin";
hlaFederate myFederate;
ObjectClassHandle squareHandle;
AttributeHandle posXHandle;
AttributeHandle posYHandle;


DLLexport void Connect() {
	ofstream log;
	log.open("LOG_pluginHLA.txt");
	log << "start " << endl;
	log.flush();
	try {
		shared_ptr<RTIambassadorFactory> rtiAmbassadorFactory(new RTIambassadorFactory());
		_rtiAmbassador = rtiAmbassadorFactory->createRTIambassador();
	}
	catch (const rti1516e::Exception&) {
		throw;
	}
	log << "created rti ambassador " << endl;
	log.flush();

	try {
		_rtiAmbassador->connect(myFederate, HLA_IMMEDIATE, localSetting);
	}
	catch (const rti1516e::Exception&) {
		throw;
	}

	log << "connected to RTI " << endl;
	log.flush();

	try {
		_rtiAmbassador->destroyFederationExecution(federationName);

		// we don't have to handle these exceptions
	}
	catch (const rti1516e::FederatesCurrentlyJoined&) {
	}
	catch (const rti1516e::FederationExecutionDoesNotExist&) {
	}
	catch (const rti1516e::RTIinternalError&) {
	}

	// Always try and create the federation execution.
	// We do this because we have no special federate that has the responsibility
	// to create the federation execution. Make sure to catch the exception!
	try {
		_rtiAmbassador->createFederationExecution(federationName, FOM);
	}
	catch (const FederationExecutionAlreadyExists&) {
		// the federation execution already exist so ignore
	}
	catch (const rti1516e::Exception& e) {
		log << e.what().c_str();
		log.flush();
		throw;
	}


	// Join the federation. If the federate name is taken add a sequence 
	// number to it to make it unique and try again. 
	bool joined = false;
	int sequenceNumber = 1;
	wstring uniqueName = federateName;

	while (!joined) {
		try {
			FederateHandle federateHandle = _rtiAmbassador->joinFederationExecution(L"normal",federationName);

			joined = true;
			federateName = uniqueName;

		}
		catch (const rti1516e::FederateNameAlreadyInUse&) {
			uniqueName = federateName + L"-";
			++sequenceNumber;
		}
	}
	log << "Joined " << endl;
	log.flush();

	try {
		squareHandle =_rtiAmbassador->getObjectClassHandle(L"Square");
		posXHandle = _rtiAmbassador->getAttributeHandle(squareHandle, L"PosX");
		posYHandle = _rtiAmbassador->getAttributeHandle(squareHandle, L"PosY");
		myFederate.setHandle(posXHandle, posYHandle);
	}
	catch (const rti1516e::Exception&) {
		throw;
	}
	log << "get Handles " << endl;
	log.close();
}
DLLexport Square Update() {
	return myFederate.getSquare();
}
