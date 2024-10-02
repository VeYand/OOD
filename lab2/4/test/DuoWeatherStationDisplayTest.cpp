#include <gtest/gtest.h>
#include "../WeatherStation/Observable/CWeatherData.h"
#include <gmock/gmock.h>

class MockDisplay final : public IObserver<SWeatherInfo>
{
public:
    MOCK_METHOD(void, Update, (const SWeatherInfo& data, IObservable<SWeatherInfo>* observable), (override));

    MockDisplay() = default;
};

TEST(DuoWeatherStationDisplay, MockObserverReceivesUpdates)
{
    CWeatherData weatherDataIn;
    CWeatherData weatherDataOut;
    MockDisplay mockDisplay;

    weatherDataIn.RegisterObserver(1, mockDisplay);
    weatherDataOut.RegisterObserver(2, mockDisplay);

    constexpr SWeatherInfo dataIn = {30, 0.5, 761.0};
    constexpr SWeatherInfo dataOut = {24, 0.75, 762.0};

    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataIn)).Times(1);
    EXPECT_CALL(mockDisplay, Update(testing::_, &weatherDataOut)).Times(1);

    weatherDataIn.SetMeasurements(dataIn.temperature, dataIn.humidity, dataIn.pressure);
    weatherDataOut.SetMeasurements(dataOut.temperature, dataOut.humidity, dataOut.pressure);
}
