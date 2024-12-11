#include "Observable/CWeatherData.h"
#include "Observer/CDisplay.h"
#include "Observer/CStatsDisplay.h"

int main()
{
    CWeatherData insideWd;
    CWeatherData outsideWd;

    CDisplay display(&insideWd, &outsideWd);
    insideWd.RegisterObserver(1, display);

    CStatsDisplay statsDisplay(&insideWd, &outsideWd);
    insideWd.RegisterObserver(2, statsDisplay);
    outsideWd.RegisterObserver(1, statsDisplay);

    outsideWd.SetMeasurements(3, 0.7, 760, {10, 10});
    insideWd.SetMeasurements(4, 0.8, 761, {1, 320});

    insideWd.RemoveObserver(statsDisplay);

    outsideWd.SetMeasurements(10, 0.8, 761, {0.2, 120});
    insideWd.SetMeasurements(-10, 0.8, 761, {1, 120});
    return 0;
}
