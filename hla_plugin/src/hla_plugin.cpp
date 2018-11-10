#include <RTI/NullFederateAmbassador.h>
#include <RTI/time/HLAinteger64TimeFactory.h>
#include <RTI/time/HLAinteger64Time.h>
#include <RTI/time/HLAinteger64Interval.h>
#include <RTI/encoding/BasicDataElements.h>
#include <RTI/encoding/HLAvariantRecord.h>
#include <RTI/encoding/HLAfixedRecord.h>
#include <RTI/RTIambassador.h>
#include <RTI/RTIambassadorFactory.h>

#define DLLexport __declspec(dllexport)

using namespace rti1516e;
using namespace std;

auto_ptr<rti1516e::RTIambassador> _rtiAmbassador;


DLLexport void connect() {
	try {
		shared_ptr<RTIambassadorFactory> rtiAmbassadorFactory(new RTIambassadorFactory());
		_rtiAmbassador = rtiAmbassadorFactory->createRTIambassador();
	}
	catch (const rti1516e::Exception&) {
		throw;
	}
}
