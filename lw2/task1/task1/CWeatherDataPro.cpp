#include "CWeatherDataPro.h"

double CWeatherDataPro::GetWindSpeed()const
{
	return m_windSpeed;
}
double CWeatherDataPro::GetWindDirection()const
{
	return m_windDirection;
}

void CWeatherDataPro::SetWindSpeed(double windSpeed)
{
	m_windSpeed = windSpeed;
	NotifyObservers(WeatherChangeEventType::WindSpeedChange);
}
void CWeatherDataPro::SetWindDirection(double windDirection)
{
	m_windDirection = windDirection;
	NotifyObservers(WeatherChangeEventType::WindDirectionChange);
}

SWeatherInfo CWeatherDataPro::GetChangedData(WeatherChangeEventType eventType)const
{
	SWeatherInfo info;
	switch (eventType)
	{
	case WeatherChangeEventType::TemperatureChange:
		info.data = GetTemperature();
		break;
	case WeatherChangeEventType::HumidityChange:
		info.data = GetHumidity();
		break;
	case WeatherChangeEventType::PressureChange:
		info.data = GetPressure();
		break;
	case WeatherChangeEventType::WindSpeedChange:
		info.data = GetWindSpeed();
		break;
	case WeatherChangeEventType::WindDirectionChange:
		info.data = GetWindDirection();
		break;
	default:
		break;
	}
	return info;
}