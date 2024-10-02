#include "Observable/CWeatherData.h"
#include "Observer/CDisplay.h"
#include "Observer/CStatsDisplay.h"

int main()
{
    CWeatherData wd;

    CDisplay display;
    wd.RegisterObserver(1, display);

    CStatsDisplay statsDisplay;
    wd.RegisterObserver(2, statsDisplay);

    wd.SetMeasurements(3, 0.7, 760, {10, 10});
    wd.SetMeasurements(4, 0.8, 761, {1, 320});

    wd.RemoveObserver(statsDisplay);

    wd.SetMeasurements(10, 0.8, 761, {0.2, 120});
    wd.SetMeasurements(-10, 0.8, 761, {1, 120});
    return 0;
}
