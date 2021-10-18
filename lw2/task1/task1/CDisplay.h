#pragma once
#include <iostream>
#include <string>
#include "Observing.h"
#include "CWeatherData.h"

class CDisplay : public CObserver<SWeatherInfo, WeatherChangeEventType>
{
	typedef IObservable<SWeatherInfo, WeatherChangeEventType> ObservableType;
public:
	CDisplay(std::shared_ptr<ObservableType> inside = nullptr, std::shared_ptr<ObservableType> outside = nullptr);
private:
	void PrintParam(std::string paramName, double param) const;
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		����asd�� CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������
	*/
	void Update(SWeatherInfo const& data, WeatherChangeEventType eventType, const ObservableType* observable) override;

private:
	std::shared_ptr<ObservableType> m_insideStation = nullptr;
	std::shared_ptr<ObservableType> m_outsideStation = nullptr;
};