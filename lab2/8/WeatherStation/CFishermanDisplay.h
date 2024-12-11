#ifndef CFISHERMANDISPLAY_H
#define CFISHERMANDISPLAY_H

#include <iostream>
#include "../Observable/IObservable.h"
#include "Model/SWeatherInfo.h"

class CFishermanDisplay final : public IObserver<SWeatherInfo, WeatherEventType>
{
public:
	CFishermanDisplay(
		IObservable<SWeatherInfo, WeatherEventType> *inStation,
		IObservable<SWeatherInfo, WeatherEventType> *outStation
	): m_inStation(inStation), m_outStation(outStation)
	{
	}

private:
	IObservable<SWeatherInfo, WeatherEventType> *m_inStation{};
	IObservable<SWeatherInfo, WeatherEventType> *m_outStation{};

	void Update(
		SWeatherInfo const &data,
		const WeatherEventType eventType,
		IObservable<SWeatherInfo, WeatherEventType> *observable
	) override
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
