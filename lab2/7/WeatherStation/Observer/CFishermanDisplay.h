#ifndef CFISHERMANDISPLAY_H
#define CFISHERMANDISPLAY_H

#include <iostream>
#include "../Observable/IObservable.h"
#include "../Model/SWeatherInfo.h"

class CFishermanDisplay final : public IObserver<SWeatherInfo>
{
	void Update(SWeatherInfo const &data, const EventType eventType) override
	{
		if (eventType == EventType::Temperature)
		{
			std::cout << "Current Temperature: " << data.temperature << std::endl;
		}
		else if (eventType == EventType::Pressure)
		{
			std::cout << "Current Pressure: " << data.pressure << std::endl;
		}
		std::cout << "----------------" << std::endl;
	}
};

#endif //CFISHERMANDISPLAY_H
