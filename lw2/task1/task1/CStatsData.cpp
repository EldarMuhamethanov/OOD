#include "CStatsData.h"
#include <iostream>

std::string CStatsData::GetParamName() const
{
	return m_paramName;
}

unsigned CStatsData::GetCountAcc() const
{
	return m_countAcc;
}

void CStatsData::IncCountAcc()
{
	++m_countAcc;
}