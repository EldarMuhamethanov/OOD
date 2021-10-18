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

	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
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