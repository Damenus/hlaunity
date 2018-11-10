//#define DLLexport __declspec(dllexport)

#include <RTI/RTI1516.h>
#include <RTI/NullFederateAmbassador.h>
#include "hlaFederate.h"
#include <iostream>

using namespace rti1516e;
using namespace std;


hlaFederate myFederate;
wstring federationName = L"square",FOM=L"Square.xml", federateName=L"Plugin Unity";
ObjectClassHandle squareHandle;
AttributeHandle PosXHandle, PosYHandle;



 void connect() {
	 auto_ptr<RTIambassador> _rtiAmbassador;
	 try {
		 shared_ptr<RTIambassadorFactory> rtiAmbassadorFactory(new RTIambassadorFactory());
		 _rtiAmbassador = rtiAmbassadorFactory->createRTIambassador();
	 }
	 catch (const rti1516e::Exception&) {
		 throw;
	 }
	 catch (std::exception e) {

	 }

	try {
		_rtiAmbassador->connect(myFederate, HLA_IMMEDIATE, L"tutorial");
	}
	catch (const rti1516e::Exception&) {
		throw;
	}

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

	vector<wstring> FOMmoduleUrls;
	FOMmoduleUrls.push_back(FOM);

	try {
		_rtiAmbassador->createFederationExecution(federationName, FOM);
	}
	catch (const FederationExecutionAlreadyExists&) {
		// the federation execution already exist so ignore
	}
	catch (const rti1516e::CouldNotOpenFDD& e) {
		throw;
	}
	catch (const rti1516e::Exception& e) {
		throw;
	}

	bool joined = false;
	int sequenceNumber = 1;
	wstring uniqueName = federateName;

	while (!joined) {
		try {
			FederateHandle federateHandle = _rtiAmbassador->joinFederationExecution(
				uniqueName,
				L"Car simulator",
				federationName,
				FOMmoduleUrls
			);

			joined = true;
			federateName = uniqueName;

		}
		catch (const rti1516e::FederateNameAlreadyInUse&) {
			uniqueName = federateName + L"-";
			++sequenceNumber;
		}
	}

	AttributeHandleSet attrHandleSet;

	squareHandle = _rtiAmbassador->getObjectClassHandle(L"Square");
	PosXHandle = _rtiAmbassador->getAttributeHandle(squareHandle, L"PosX");
	attrHandleSet.insert(PosXHandle);
	PosYHandle = _rtiAmbassador->getAttributeHandle(squareHandle, L"PosY");
	attrHandleSet.insert(PosYHandle);

	myFederate.setAtributeHandle(PosXHandle, PosYHandle);

	try {
		_rtiAmbassador->subscribeObjectClassAttributes(squareHandle, attrHandleSet);
	}
	catch (const rti1516e::Exception&) {
		throw;
	}
}

 square getSquare() {
	return myFederate.getSquare();
}

 int main()
 {
	 connect();	
	 cout << "\nconnected";
	 while (true)
	 {

	 }
	 return 0;
 }