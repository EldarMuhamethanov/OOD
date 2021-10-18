#pragma once
#include <iostream>
#include <climits>
#include <string>

class CStatsData
{
public:
	CStatsData(const std::string& paramName) : m_paramName(paramName) {}
	virtual ~CStatsData() = default;
	virtual void Update(double value) = 0;
	virtual double GetAverageValue() const = 0;
	virtual void PrintData() const = 0;

	std::string GetParamName() const;
	unsigned GetCountAcc() const;
	void IncCountAcc();
private:
	std::string m_paramName = "";
	unsigned m_countAcc = 0;
};