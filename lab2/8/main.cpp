#include "WeatherStation/CWeatherData.h"
#include "WeatherStation/CFishermanDisplay.h"

void WorkWithFisherman()
{
	CWeatherData wd;

	CFishermanDisplay display;
	wd.RegisterObserver(5, display, WeatherEventType::Temperature);

	wd.SetMeasurements(25, 0.4, 760, {10, 10});

	wd.SetMeasurements(10, 0.8, 761, {10, 10});
}

int main()
{
	WorkWithFisherman();

	return 0;
}
