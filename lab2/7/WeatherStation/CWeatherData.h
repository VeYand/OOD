#ifndef CWEATHERDATA_H
#define CWEATHERDATA_H

#include "../Observable/CObservable.h"
#include "Model/SWeatherInfo.h"

enum class WeatherEventType
{
	Temperature,
	Pressure,
	Humidity,
	Wind,
};

class CWeatherData final : public CObservable<SWeatherInfo, WeatherEventType>
{
public:
	// Температура в градусах Цельсия
	[[nodiscard]] double GetTemperature() const
	{
		return m_temperature;
	}

	// Относительная влажность (0...100)
	[[nodiscard]] double GetHumidity() const
	{
		return m_humidity;
	}

	// Атмосферное давление (в мм.рт.ст)
	[[nodiscard]] double GetPressure() const
	{
		return m_pressure;
	}

	[[nodiscard]] SWindInfo GetWindInfo() const
	{
		return m_wind;
	}

	void MeasurementsChanged(const WeatherEventType eventType)
	{
		NotifyObservers(eventType);
	}

	void SetTemp(const double temp)
	{
		m_temperature = temp;

		MeasurementsChanged(WeatherEventType::Temperature);
	}

	void SetHumidity(const double humidity)
	{
		m_humidity = humidity;

		MeasurementsChanged(WeatherEventType::Humidity);
	}

	void SetPressure(const double pressure)
	{
		m_pressure = pressure;

		MeasurementsChanged(WeatherEventType::Pressure);
	}

	void SetMeasurements(const double temp, const double humidity, const double pressure, const SWindInfo &wind)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_wind = wind;

		MeasurementsChanged(WeatherEventType::Temperature);
		MeasurementsChanged(WeatherEventType::Pressure);
		MeasurementsChanged(WeatherEventType::Humidity);
		MeasurementsChanged(WeatherEventType::Wind);
	}

protected:
	[[nodiscard]] SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.wind = GetWindInfo();

		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	SWindInfo m_wind{};
};

#endif //CWEATHERDATA_H
