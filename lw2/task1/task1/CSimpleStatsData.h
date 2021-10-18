#pragma once
#include "CStatsData.h"

class CSimpleStatsData : public CStatsData
{
public:
	CSimpleStatsData(const std::string& paramName) : CStatsData(paramName){}
	void Update(double value) override;
	double GetAverageValue() const override;
	void PrintData() const override;
private:
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
};

class CTemperatureStatsData : public CSimpleStatsData
{
public:
	CTemperatureStatsData() : CSimpleStatsData("Temp") {}
};

class CHumidityStatsData : public CSimpleStatsData
{
public:
	CHumidityStatsData() : CSimpleStatsData("Hum") {}
};

class CPressureStatsData : public CSimpleStatsData
{
public:
	CPressureStatsData() : CSimpleStatsData("Pressure") {}
};

class CWindSpeedStatsData : public CSimpleStatsData
{
public:
	CWindSpeedStatsData() : CSimpleStatsData("Wind Speed") {}
};