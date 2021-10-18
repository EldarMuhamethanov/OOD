#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observing.h"
#include "Observing.h"


enum class WeatherChangeEventType
{
	TemperatureChange,
	HumidityChange,
	PressureChange,
	WindSpeedChange,
	WindDirectionChange,
};
struct SWeatherInfo
{
	double data = 0;
};

class CWeatherData : public CObservable<SWeatherInfo, WeatherChangeEventType>
{
public:
	CWeatherData() {}

	// Температура в градусах Цельсия
	double GetTemperature()const;
	// Относительная влажность (0...100)
	double GetHumidity()const;
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const;
	void SetTemperature(double temp);
	void SetHumidity(double humidity);
	void SetPressure(double pressure);
protected:
	SWeatherInfo GetChangedData(WeatherChangeEventType eventType)const override;
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

