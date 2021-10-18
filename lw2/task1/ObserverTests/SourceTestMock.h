#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <stack>
//#include "../task1/CWeatherDataInside.h"
//#include "../task1/CWeatherDataOutside.h"
#include "../task1/CWeatherData.h"
#include "../task1/Observing.h"

class SourceTestMockObserver : public IObserver<SWeatherInfo, WeatherChangeEventType>
{
public:
	SourceTestMockObserver(std::shared_ptr<IObservable<SWeatherInfo, WeatherChangeEventType>> inside, std::shared_ptr<IObservable<SWeatherInfo, WeatherChangeEventType>> outside)
		: m_insideStation(inside)
		, m_outsideStation(outside)
	{}
	SourceTestMockObserver()
		: m_sourceType("")
	{}
	std::string GetSourceType()
	{
		return m_sourceType;
	}
private:
	void Update(SWeatherInfo const& data, WeatherChangeEventType eventType, const IObservable<SWeatherInfo, WeatherChangeEventType>* observable) override
	{
		if (m_insideStation.get() == observable)
		{
			m_sourceType = "Inside";
		}
		else if (m_outsideStation.get() == observable)
		{
			m_sourceType = "Outside";
		}
	}
private:
	std::shared_ptr<IObservable<SWeatherInfo, WeatherChangeEventType>> m_insideStation = nullptr;
	std::shared_ptr<IObservable<SWeatherInfo, WeatherChangeEventType>> m_outsideStation = nullptr;
	std::string m_sourceType;
};
