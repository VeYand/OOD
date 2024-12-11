#ifndef CDISPLAY_H
#define CDISPLAY_H

#include <iostream>
#include "../Observable/IObservable.h"
#include "../Model/SWeatherInfo.h"

class CDisplay final : public IObserver<SWeatherInfo>
{
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	    Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	    остается публичным
	*/
	void Update(SWeatherInfo const &data) override
	{
		std::cout << "Current wind speed " << data.wind.speed << std::endl;
		std::cout << "Current wind direction " << data.wind.direction << " degrees" << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

#endif //CDISPLAY_H
