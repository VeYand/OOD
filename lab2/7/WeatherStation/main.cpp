#include "Observable/CWeatherData.h"
#include "Observer/CFishermanDisplay.h"

int main()
{
	CWeatherData wd;

	CFishermanDisplay display;
	wd.RegisterObserver(5, display, EventType::Temperature);

	wd.SetMeasurements(25, 0.4, 760, {10, 10});

	wd.SetMeasurements(10, 0.8, 761, {10, 10});

	return 0;
}
