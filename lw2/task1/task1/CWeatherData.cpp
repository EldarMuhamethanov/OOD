#include "CWeatherData.h"

// Температура в градусах Цельсия
double CWeatherData::GetTemperature()const
{
	return m_temperature;
}
// Относительная влажность (0...100)
double CWeatherData::GetHumidity()const
{
	return m_humidity;
}
// Атмосферное давление (в мм.рт.ст)
double CWeatherData::GetPressure()const
{
	return m_pressure;
}
void CWeatherData::SetTemperature(double temp)
{
	m_temperature = temp;
	NotifyObservers(WeatherChangeEventType::TemperatureChange);
}
void CWeatherData::SetHumidity(double humidity)
{
	m_humidity = humidity;
	NotifyObservers(WeatherChangeEventType::HumidityChange);
}
void CWeatherData::SetPressure(double pressure)
{
	m_pressure = pressure;
	NotifyObservers(WeatherChangeEventType::PressureChange);
}

SWeatherInfo CWeatherData::GetChangedData(WeatherChangeEventType eventType)const
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
	default:
		throw std::invalid_argument("unexpected event type");
		break;
	}
	return info;
}