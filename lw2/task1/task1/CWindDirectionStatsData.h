#pragma once
#include "CStatsData.h"

class CWindDirectionStatsData : public CStatsData
{
public:
	CWindDirectionStatsData() : CStatsData("Wind Direction") {}
	void Update(double value) override;
	double GetAverageValue() const override;
	void PrintData() const override;
private:
	double m_sinusSum = 0;
	double m_cosineSum = 0;
};