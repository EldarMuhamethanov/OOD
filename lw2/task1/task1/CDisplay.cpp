#include "CDisplay.h"
#include "CWeatherData.h"
#include "CWeatherDataInside.h"
#include "CWeatherDataOutside.h"


CDisplay::CDisplay(std::shared_ptr<ObservableType> inside, std::shared_ptr<ObservableType> outside)
	: m_insideStation(inside)
	, m_outsideStation(outside)
{}

void CDisplay::PrintParam(std::string paramName, double param) const
{
	std::cout << "Current " << paramName << " " << param << std::endl;;
}

void CDisplay::Update(SWeatherInfo const& data, WeatherChangeEventType eventType, const ObservableType* observable)
{
	if (m_insideStation.get() == observable)
	{
		std::cout << "Weather data inside" << std::endl;
	}
	else if (m_outsideStation.get() == observable)
	{
		std::cout << "Weather data outside" << std::endl;
	}

	switch (eventType)
	{
	case WeatherChangeEventType::TemperatureChange:
		PrintParam("Temp", data.data);
		break;
	case WeatherChangeEventType::HumidityChange:
		PrintParam("Hum", data.data);
		break;
	case WeatherChangeEventType::PressureChange:
		PrintParam("Pressure", data.data);
		break;
	case WeatherChangeEventType::WindSpeedChange:
		PrintParam("Wind Speed", data.data);
		break;
	case WeatherChangeEventType::WindDirectionChange:
		PrintParam("Wind Direction", data.data);
		break;
	default:
		break;
	}
	std::cout << "----------------" << std::endl;
}