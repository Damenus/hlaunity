#define DLLexport extern "C"  __declspec(dllexport)
#include <iostream>
#include <RTI/RTIambassadorFactory.h>
#include <fstream>
#include "hlaFederate.h"
#include <RTI/RTIambassador.h>
#include <Windows.h>
#include "hlaPlugin.h"
//#include "Square.h"
#include <RTI/encoding/HLAfixedRecord.h>
#include <RTI/encoding/BasicDataElements.h>

using namespace std;
using namespace rti1516e;

auto_ptr<RTIambassador> _rtiAmbassador;
wstring FOM = L"Square.xml",localSetting= L"tutorial", federationName=L"Square try", federateName = L"Unity plugin";
hlaFederate myFederate;
ObjectClassHandle squareHandle;
AttributeHandle posXHandle;
AttributeHandle posYHandle;
ObjectInstanceHandle sqrInstanceHandle;
InteractionClassHandle squareRecived;
HLAfloat32BE   floatDecode;


DLLexport void Connect() {
	ofstream log;
	log.open("LOG_pluginHLA.txt");
	log << "start " << endl;
	log.flush();
	try {
		shared_ptr<RTIambassadorFactory> rtiAmbassadorFactory(new RTIambassadorFactory());
		_rtiAmbassador = rtiAmbassadorFactory->createRTIambassador();
	}
	catch (const rti1516e::Exception& e) {
		log << e.what().c_str();
		log.flush();
		throw;
	}
	log << "created rti ambassador " << endl;
	log.flush();

	try {
		_rtiAmbassador->connect(myFederate, HLA_IMMEDIATE, localSetting);
	}
	catch (const rti1516e::Exception& e) {
		log << e.what().c_str();
		log.flush();
		throw;
	}

	log << "connected to RTI " << endl;
	log.flush();

	try {
		_rtiAmbassador->destroyFederationExecution(federationName);

		// we don't have to handle these exceptions
	}
	catch (const rti1516e::FederatesCurrentlyJoined& e) {
		log << e.what().c_str();
		log.flush();
	}
	catch (const rti1516e::FederationExecutionDoesNotExist& e) {
		log << e.what().c_str();
		log.flush();
	}
	catch (const rti1516e::RTIinternalError& e) {
		log << e.what().c_str();
		log.flush();
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
			FederateHandle federateHandle = _rtiAmbassador->joinFederationExecution(federateName,federationName);

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

		//rejestracja 
		AttributeHandleSet carAttributes;
		carAttributes.insert(posXHandle);
		carAttributes.insert(posYHandle);
		_rtiAmbassador->publishObjectClassAttributes(squareHandle, carAttributes);
		//subskrybcja
		_rtiAmbassador->subscribeObjectClassAttributes(squareHandle, carAttributes);
		
		sqrInstanceHandle = _rtiAmbassador->registerObjectInstance(squareHandle);

		
		AttributeHandleValueMap attributeMap;

		floatDecode.set(myFederate.mainSquare.PozX);
		attributeMap[posXHandle] = floatDecode.encode();
		floatDecode.set(myFederate.mainSquare.PozY);
		attributeMap[posYHandle] = floatDecode.encode();

		try {
			_rtiAmbassador->updateAttributeValues(sqrInstanceHandle, attributeMap, VariableLengthData());
		}
		catch (const rti1516e::Exception&) {
			// Internal data structures are still valid so no clean up is performed
		}
	}
	catch (const rti1516e::Exception&) {
		throw;
	}
	log << "get Handles " << endl;
	log.close();
}

void subscribeSquare()
{

}

// Updating a car involves calling updateAttributeValues for the given car object using
// the RTI Ambassador.
DLLexport void UpdatePosition() throw (rti1516e::EncoderException)
{
	
	AttributeHandleValueMap attributeMap;

	floatDecode.set(myFederate.mainSquare.PozX);
	attributeMap[posXHandle] = floatDecode.encode();
	floatDecode.set(myFederate.mainSquare.PozY);
	attributeMap[posYHandle] = floatDecode.encode();

	try {
		_rtiAmbassador->updateAttributeValues(sqrInstanceHandle, attributeMap, VariableLengthData());
	}
	catch (const rti1516e::Exception&) {
		// Internal data structures are still valid so no clean up is performed
	}
}

DLLexport Square GetSquare() {
	return myFederate.getSquare();
}

DLLexport float GetSquareX() {
	return myFederate.getSquare().PozX;
}

DLLexport float GetSquareY() {
	return myFederate.getSquare().PozY;
}

DLLexport void SetSquareX(float x) {
	myFederate.setSquareX(x);
}

DLLexport void SetSquareY(float y) {
	myFederate.setSquareY(y);
}
