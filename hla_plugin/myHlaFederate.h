#pragma once
#include <RTI/NullFederateAmbassador.h>
#include <RTI/encoding/BasicDataElements.h>
#include <RTI/encoding/HLAfixedRecord.h>
#include <RTI/RTIambassador.h>
#include "Vehicle.h"
#include "Player.h"
#include <algorithm>
#include <fstream>

using namespace std;
using namespace rti1516e;

class myHlaFederate : public NullFederateAmbassador
{
public:
	auto_ptr<RTIambassador> _rtiAmbassador;

	vector<Vehicle> _vehicles;
	vector<Player> _players;

	ofstream _log;


	myHlaFederate();
	~myHlaFederate();

	void log(string logMessage);


	////////////////////////////////////////////////////////
	//  Implementation methods to handle discovery event //
	///////////////////////////////////////////////////////
	void discoverObjectInstanceImpl(
		ObjectInstanceHandle theObject,
		ObjectClassHandle theObjectClass)
		throw (
			FederateInternalError);

	////////////////////////////////////////////////////////
	//  Implementation methods to handle discovery event //
	///////////////////////////////////////////////////////
	void reflectAttributeValuesImpl(
		ObjectInstanceHandle theObject,
		AttributeHandleValueMap const & theAttributeValues)
		throw (
			FederateInternalError);

	/////////////////////////////////////////////////////////////////
	//  Implementation methods to handle receive interaction event //
	/////////////////////////////////////////////////////////////////
	void receiveInteractionImpl(
		InteractionClassHandle theInteraction,
		ParameterHandleValueMap const & theParameterValues)
		throw (
			FederateInternalError);

	////////////////////////////////////////////////////////////
	//  Implementation methods to handle remove object event //
	///////////////////////////////////////////////////////////
	void removeObjectInstanceImpl(
		ObjectInstanceHandle theObject)
		throw (
			FederateInternalError);

	////////////////////////////////////////////////////////////////
	//  Implementation methods to handle provide Attribute event //
	///////////////////////////////////////////////////////////////
	void provideAttributeValueUpdateImpl(
		ObjectInstanceHandle theObject,
		AttributeHandleSet const & theAttributes)
		throw (
			FederateInternalError);

	///////////////////////////////////////////////////////////////////////////
	//  Methods to recive hla event. only transmit to implementation method  //
	///////////////////////////////////////////////////////////////////////////

	//////////////////
	//  Discovery  //
	/////////////////
	 void discoverObjectInstance(
		ObjectInstanceHandle theObject,
		ObjectClassHandle theObjectClass,
		std::wstring const & theObjectInstanceName)
		throw (
			FederateInternalError);

	 void discoverObjectInstance(
		ObjectInstanceHandle theObject,
		ObjectClassHandle theObjectClass,
		std::wstring const & theObjectInstanceName,
		FederateHandle producingFederate)
		throw (
			FederateInternalError);

	////////////////
	//  Reflect  //
	///////////////
	 void reflectAttributeValues(
		ObjectInstanceHandle theObject,
		AttributeHandleValueMap const & theAttributeValues,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		TransportationType theType,
		SupplementalReflectInfo theReflectInfo)
		throw (
			FederateInternalError);

	 void reflectAttributeValues(
		ObjectInstanceHandle theObject,
		AttributeHandleValueMap const & theAttributeValues,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		TransportationType theType,
		LogicalTime const & theTime,
		OrderType receivedOrder,
		SupplementalReflectInfo theReflectInfo)
		throw (
			FederateInternalError);

	 void reflectAttributeValues(
		ObjectInstanceHandle theObject,
		AttributeHandleValueMap const & theAttributeValues,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		TransportationType theType,
		LogicalTime const & theTime,
		OrderType receivedOrder,
		MessageRetractionHandle theHandle,
		SupplementalReflectInfo theReflectInfo)
		throw (
			FederateInternalError);
	////////////////
	//  Receive  //
	///////////////
	 void receiveInteraction(
		InteractionClassHandle theInteraction,
		ParameterHandleValueMap const & theParameterValues,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		TransportationType theType,
		SupplementalReceiveInfo theReceiveInfo)
		throw (
			FederateInternalError);

	 void receiveInteraction(
		InteractionClassHandle theInteraction,
		ParameterHandleValueMap const & theParameterValues,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		TransportationType theType,
		LogicalTime const & theTime,
		OrderType receivedOrder,
		SupplementalReceiveInfo theReceiveInfo)
		throw (
			FederateInternalError);

	 void receiveInteraction(
		InteractionClassHandle theInteraction,
		ParameterHandleValueMap const & theParameterValues,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		TransportationType theType,
		LogicalTime const & theTime,
		OrderType receivedOrder,
		MessageRetractionHandle theHandle,
		SupplementalReceiveInfo theReceiveInfo)
		throw (
			FederateInternalError);
	///////////////
	//  remove  //
	//////////////
	 void removeObjectInstance(
		ObjectInstanceHandle theObject,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		SupplementalRemoveInfo theRemoveInfo)
		throw (
			FederateInternalError);

	 void removeObjectInstance(
		ObjectInstanceHandle theObject,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		LogicalTime const & theTime,
		OrderType receivedOrder,
		SupplementalRemoveInfo theRemoveInfo)
		throw (
			FederateInternalError);

	 void removeObjectInstance(
		ObjectInstanceHandle theObject,
		VariableLengthData const & theUserSuppliedTag,
		OrderType sentOrder,
		LogicalTime const & theTime,
		OrderType receivedOrder,
		MessageRetractionHandle theHandle,
		SupplementalRemoveInfo theRemoveInfo)
		throw (
			FederateInternalError);
	///////////////
	//  provide  //
	//////////////
	 void provideAttributeValueUpdate(
		ObjectInstanceHandle theObject,
		AttributeHandleSet const & theAttributes,
		VariableLengthData const & theUserSuppliedTag)
		throw (
			FederateInternalError);
};

