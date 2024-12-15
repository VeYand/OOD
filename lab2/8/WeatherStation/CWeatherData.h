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
	[[nodiscard]] double GetTemperature() const
	{
		return m_temperature;
	}

	[[nodiscard]] double GetHumidity() const
	{
		return m_humidity;
	}

	[[nodiscard]] double GetPressure() const
	{
		return m_pressure;
	}

	[[nodiscard]] SWindInfo GetWindInfo() const
	{
		return m_wind;
	}

	void SetTemp(double temp)
	{
		m_temperature = temp;
		NotifyObservers(WeatherEventType::Temperature);
	}

	void SetHumidity(double humidity)
	{
		m_humidity = humidity;
		NotifyObservers(WeatherEventType::Humidity);
	}

	void SetPressure(double pressure)
	{
		m_pressure = pressure;
		NotifyObservers(WeatherEventType::Pressure);
	}

	void SetMeasurements(double temp, double humidity, double pressure, const SWindInfo &wind)
	{
		m_temperature = temp;
		m_humidity = humidity;
		m_pressure = pressure;
		m_wind = wind;

		NotifyObservers(WeatherEventType::Temperature);
		NotifyObservers(WeatherEventType::Pressure);
		NotifyObservers(WeatherEventType::Humidity);
		NotifyObservers(WeatherEventType::Wind);
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
	SWindInfo m_wind;
};

#endif // CWEATHERDATA_H
