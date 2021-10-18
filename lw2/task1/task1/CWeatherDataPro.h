#pragma once
#include "CWeatherData.h"

class CWeatherDataPro : public CWeatherData
{
public:
	CWeatherDataPro() {}
	double GetWindSpeed()const;
	double GetWindDirection()const;
	void SetWindSpeed(double windSpeed);
	void SetWindDirection(double windDirection);
protected:
	SWeatherInfo GetChangedData(WeatherChangeEventType eventType)const override;
private:
	double m_windSpeed = 0;
	double m_windDirection = 0;
};
