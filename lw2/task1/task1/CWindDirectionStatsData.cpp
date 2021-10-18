#include "CWindDirectionStatsData.h"
#include <cmath>

const double M_PI = 3.14;

double ConvertToRadians(double value)
{
	return value * M_PI / 180;
}

double ConvertToDegrees(double value)
{
	return value * 180 / M_PI;
}

void CWindDirectionStatsData::Update(double value)
{
	m_sinusSum += sin(ConvertToRadians(value));
	m_cosineSum += cos(ConvertToRadians(value));
}

double CWindDirectionStatsData::GetAverageValue() const
{
	double x = ConvertToDegrees(atan2(m_sinusSum, m_cosineSum)) + 360;
	return x - trunc(x / 360) * 360;
}

void CWindDirectionStatsData::PrintData() const
{
	std::string paramName = GetParamName();
	double avgValue = GetAverageValue();
	std::cout << "Average " << paramName << " " << avgValue << std::endl;
	std::cout << "----------------" << std::endl;
}