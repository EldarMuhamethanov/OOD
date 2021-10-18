#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "PriorityMock.h"
#include "SafelyNotifyMock.h"
#include "../task1/CWeatherData.h"
#include "../task1/CWeatherDataInside.h"
#include "../task1/CWeatherDataOutside.h"
#include "SourceTestMock.h"
#include "../task1/CDisplay.h"

using namespace std;

SCENARIO("Safely notify observers")
{
	std::stack<std::string> callStack;

	SafelyMockObservable mockObservable;

	SafelyMockObserver mockObserver1("Obs 1", callStack, mockObservable);
	SafelyMockObserver mockObserver2("Obs 2", callStack, mockObservable);

	mockObservable.RegisterObserver(mockObserver1, SafelyMockEventType::Event, 10);
	mockObservable.RegisterObserver(mockObserver2, SafelyMockEventType::Event, 15);

	std::stack<std::string> finalCallStack;

	finalCallStack.push("Obs 2");
	finalCallStack.push("Obs 1");

	mockObservable.CallNotifyObservers();
	REQUIRE(callStack == finalCallStack);

	mockObservable.CallNotifyObservers();
	REQUIRE(callStack == finalCallStack);
}

SCENARIO("Test priority")
{
	std::stack<std::string> callStack;

	PriorityMockObserver mockObserver1("Obs 1", callStack);
	PriorityMockObserver mockObserver2("Obs 2", callStack);

	PriorityMockObservable mockObservable;

	WHEN("notify mockObserver2 then mockObserver1")
	{
		mockObservable.RegisterObserver(mockObserver1, PriorityMockEventType::Event, 10);
		mockObservable.RegisterObserver(mockObserver2, PriorityMockEventType::Event, 15);

		std::stack<std::string> finalCallStack;

		finalCallStack.push("Obs 2");
		finalCallStack.push("Obs 1");

		mockObservable.CallNotifyObservers();

		REQUIRE(callStack == finalCallStack);
	}
	WHEN("notify mockObserver1 then mockObserver2")
	{
		mockObservable.RegisterObserver(mockObserver1, PriorityMockEventType::Event, 15);
		mockObservable.RegisterObserver(mockObserver2, PriorityMockEventType::Event, 14);

		std::stack<std::string> finalCallStack;

		finalCallStack.push("Obs 1");
		finalCallStack.push("Obs 2");

		mockObservable.CallNotifyObservers();

		REQUIRE(callStack == finalCallStack);
	}
}

SCENARIO("Test Weather Station Duo")
{
	shared_ptr<CWeatherDataInside> weatherDataIn = make_shared<CWeatherDataInside>();
	shared_ptr<CWeatherDataOutside> weatherDataOut = make_shared<CWeatherDataOutside>();

	SourceTestMockObserver mockObserver1(weatherDataIn, weatherDataOut);

	weatherDataIn->RegisterObserver(mockObserver1, WeatherChangeEventType::TemperatureChange, 10);
	weatherDataOut->RegisterObserver(mockObserver1, WeatherChangeEventType::TemperatureChange,10);
	WHEN("observe inside")
	{
		weatherDataIn->SetTemperature(5);
		REQUIRE(mockObserver1.GetSourceType() == "Inside");
	}

	WHEN("observe outside")
	{
		weatherDataOut->SetTemperature(5);
		REQUIRE(mockObserver1.GetSourceType() == "Outside");
	}
}
