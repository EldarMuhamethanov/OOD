#include "CStatsDisplay.h"
#include "CWeatherData.h"
#include "CWeatherDataInside.h"
#include "CWeatherDataOutside.h"

CStatsDisplay::CStatsDisplay(std::shared_ptr<ObservableType> inside, std::shared_ptr<ObservableType> outside)
	: m_insideStation(inside)
	, m_outsideStation(outside)
{}

void CStatsDisplay::Update(SWeatherInfo const& data, WeatherChangeEventType eventType, const ObservableType* observable)
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
		m_temperature.Update(data.data);
		m_temperature.PrintData();
		break;
	case WeatherChangeEventType::HumidityChange:
		m_humidity.Update(data.data);
		m_humidity.PrintData();
		break;
	case WeatherChangeEventType::PressureChange:
		m_pressure.Update(data.data);
		m_pressure.PrintData();
		break;
	case WeatherChangeEventType::WindSpeedChange:
		m_windSpeed.Update(data.data);
		m_windSpeed.PrintData();
		break;
	case WeatherChangeEventType::WindDirectionChange:
		m_windDirection.Update(data.data);
		m_windDirection.PrintData();
		break;
	default:
		break;
	}
}