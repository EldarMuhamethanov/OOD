#include <map>
#include <vector>
#include <string>
#include "CWeatherDataInside.h"
#include "CWeatherDataOutside.h"
#include "CDisplay.h"
#include "CStatsDisplay.h"
#include "Observing.h"
#include <algorithm>

using namespace std;

int main()
{
	shared_ptr<CWeatherDataInside> wdIn = make_shared<CWeatherDataInside>();
	shared_ptr<CWeatherDataOutside> wdOut = make_shared<CWeatherDataOutside>();

	CStatsDisplay statsDisplay(wdIn, wdOut);
	CDisplay display(wdIn, wdOut);
	wdIn->RegisterObserver(statsDisplay, WeatherChangeEventType::TemperatureChange, 4);
	wdOut->RegisterObserver(statsDisplay, WeatherChangeEventType::HumidityChange, 4);
	wdIn->RegisterObserver(display, WeatherChangeEventType::TemperatureChange, 3);
	wdIn->SetTemperature(10);
	wdIn->SetTemperature(11);
	wdOut->SetHumidity(15);

	return 0;
}