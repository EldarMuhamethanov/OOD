#include "CSimpleStatsData.h"

void CSimpleStatsData::Update(double value)
{
	if (m_minValue > value)
	{
		m_minValue = value;
	}
	if (m_maxValue < value)
	{
		m_maxValue = value;
	}
	m_accValue += value;
	IncCountAcc();
}

double CSimpleStatsData::GetAverageValue() const
{
	return (m_accValue / GetCountAcc());
}

void CSimpleStatsData::PrintData() const
{
	std::string paramName = GetParamName();
	double minValue = m_minValue;
	double maxValue = m_maxValue;
	double avgValue = GetAverageValue();
	std::cout << "Max " << paramName << " " << maxValue << std::endl;
	std::cout << "Min " << paramName << " " << minValue << std::endl;
	std::cout << "Average " << paramName << " " << avgValue << std::endl;
	std::cout << "----------------" << std::endl;
}