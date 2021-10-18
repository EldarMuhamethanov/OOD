#pragma once
#include <iostream>
#include <memory>
#include "Observing.h"
#include "CWeatherData.h"
#include "CSimpleStatsData.h"
#include "CWindDirectionStatsData.h"

class CStatsDisplay : public CObserver<SWeatherInfo, WeatherChangeEventType>
{
	typedef IObservable<SWeatherInfo, WeatherChangeEventType> ObservableType;
public:
	CStatsDisplay(std::shared_ptr<ObservableType> inside = nullptr, std::shared_ptr<ObservableType> outside = nullptr);
private:

	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, WeatherChangeEventType eventType, const ObservableType* observable) override;

	CTemperatureStatsData m_temperature;
	CHumidityStatsData m_humidity;
	CPressureStatsData m_pressure;
	CWindSpeedStatsData m_windSpeed;
	CWindDirectionStatsData m_windDirection;
private:
	std::shared_ptr<ObservableType> m_insideStation = nullptr;
	std::shared_ptr<ObservableType> m_outsideStation = nullptr;
};