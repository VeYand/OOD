#ifndef CSTATSDISPLAY_H
#define CSTATSDISPLAY_H

#include <iostream>

#include "CStatistics.h"
#include "CWindStatistics.h"
#include "../Observable/IObservable.h"
#include "../Model/SWeatherInfo.h"

class CStatsDisplay final : public IObserver<SWeatherInfo>
{
public:
    CStatsDisplay(
        IObservable<SWeatherInfo> *inStation,
        IObservable<SWeatherInfo> *outStation
    ): m_inStation(inStation), m_outStation(outStation)
    {
    }

private:
    IObservable<SWeatherInfo> *m_inStation{};
    IObservable<SWeatherInfo> *m_outStation{};

    /* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
    Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
    остается публичным
    */
    void Update(SWeatherInfo const &data, IObservable<SWeatherInfo> *observable) override
    {
        m_temperatureStatistics.AddValue(data.temperature);
        m_humidityStatistics.AddValue(data.humidity);
        m_pressureStatistics.AddValue(data.pressure);
        m_windStatistics.AddValue(data.wind);

        if (observable == m_inStation)
        {
            std::cout << "Inside station" << std::endl;
        }
        else if (observable == m_outStation)
        {
            std::cout << "Outside station" << std::endl;
            std::cout << "Max wind speed " << m_windStatistics.GetMaxSpeed() << std::endl;
            std::cout << "Min wind speed " << m_windStatistics.GetMinSpeed() << std::endl;
            std::cout << "Average wind speed " << m_windStatistics.GetAverageSpeed() << std::endl;
            std::cout << "Average wind direction " << m_windStatistics.GetAverageDirection() << " degrees" << std::endl;
        }
        else
        {
            std::cout << "Unknown station" << std::endl;
        }

        std::cout << "Max Temp " << m_temperatureStatistics.GetMax() << std::endl;
        std::cout << "Min Temp " << m_temperatureStatistics.GetMin() << std::endl;
        std::cout << "Average Temp " << m_temperatureStatistics.GetAverage() << std::endl;

        std::cout << "Max Hum " << m_humidityStatistics.GetMax() << std::endl;
        std::cout << "Min Hum " << m_humidityStatistics.GetMin() << std::endl;
        std::cout << "Average Hum " << m_humidityStatistics.GetAverage() << std::endl;

        std::cout << "Max Pressure " << m_pressureStatistics.GetMax() << std::endl;
        std::cout << "Min Pressure " << m_pressureStatistics.GetMin() << std::endl;
        std::cout << "Average Pressure " << m_pressureStatistics.GetAverage() << std::endl;

        std::cout << "----------------" << std::endl;
    }

    CStatistics m_temperatureStatistics{};
    CStatistics m_humidityStatistics{};
    CStatistics m_pressureStatistics{};
    CWindStatistics m_windStatistics{};
};

#endif //CSTATSDISPLAY_H
