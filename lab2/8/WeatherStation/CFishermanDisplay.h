#ifndef CFISHERMANDISPLAY_H
#define CFISHERMANDISPLAY_H

#include <iostream>
#include "../Observable/IObservable.h"
#include "Model/SWeatherInfo.h"

class CFishermanDisplay final : public IObserver<SWeatherInfo, WeatherEventType>
{
	void Update(SWeatherInfo const &data, const WeatherEventType eventType) override
	{
		if (eventType == WeatherEventType::Temperature)
		{
			std::cout << "Current Temperature: " << data.temperature << std::endl;
		}
		else if (eventType == WeatherEventType::Pressure)
		{
			std::cout << "Current Pressure: " << data.pressure << std::endl;
		}
		std::cout << "----------------" << std::endl;
	}
};

#endif //CFISHERMANDISPLAY_H
