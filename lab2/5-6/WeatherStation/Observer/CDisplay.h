#ifndef CDISPLAY_H
#define CDISPLAY_H
#include <iostream>

#include "IObserver.h"
#include "../Model/SWeatherInfo.h"

class CDisplay final : public IObserver<SWeatherInfo>
{
public:
    CDisplay(
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
        if (observable == m_inStation)
        {
            std::cout << "Inside station" << std::endl;
        }
        else if (observable == m_outStation)
        {
            std::cout << "Outside station" << std::endl;
        }
        else
        {
            std::cout << "Unknown station" << std::endl;
        }
        std::cout << "Current Temp " << data.temperature << std::endl;
        std::cout << "Current Hum " << data.humidity << std::endl;
        std::cout << "Current Pressure " << data.pressure << std::endl;
        std::cout << "----------------" << std::endl;
    }
};

#endif //CDISPLAY_H
