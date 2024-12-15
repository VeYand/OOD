#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../WeatherStation/CWeatherData.h"
#include "../WeatherStation/Model/SWeatherInfo.h"

class MockObserver final : public IObserver<SWeatherInfo, WeatherEventType>
{
public:
    using iot = IObservable<SWeatherInfo, WeatherEventType>;
    MOCK_METHOD(void, Update, (const SWeatherInfo& data, WeatherEventType eventType, iot* observable), (override));
};

TEST(CWeatherDataTests, NotifySingleObserver)
{
    CWeatherData weatherData;
    MockObserver mockObserver;

    weatherData.RegisterObserver(0, mockObserver, WeatherEventType::Temperature);

    EXPECT_CALL(mockObserver, Update(testing::_, WeatherEventType::Temperature, testing::_)).Times(1);

    weatherData.SetTemp(25.0);
}

TEST(CWeatherDataTests, NotifyMultipleObservers)
{
    CWeatherData weatherData;
    MockObserver observer1, observer2;

    weatherData.RegisterObserver(0, observer1, WeatherEventType::Temperature);
    weatherData.RegisterObserver(1, observer2, WeatherEventType::Temperature);

    EXPECT_CALL(observer1, Update(testing::_, WeatherEventType::Temperature, testing::_)).Times(1);
    EXPECT_CALL(observer2, Update(testing::_, WeatherEventType::Temperature, testing::_)).Times(1);

    weatherData.SetTemp(20.0);
}

TEST(CWeatherDataTests, RemoveObserver)
{
    CWeatherData weatherData;
    MockObserver observer;

    weatherData.RegisterObserver(0, observer, WeatherEventType::Temperature);
    weatherData.RemoveObserver(observer, WeatherEventType::Temperature);

    EXPECT_CALL(observer, Update(testing::_, testing::_, testing::_)).Times(0);

    weatherData.SetTemp(30.0);
}

TEST(CWeatherDataTests, NotifyDifferentEvents)
{
    CWeatherData weatherData;
    MockObserver mockObserver;

    weatherData.RegisterObserver(0, mockObserver, WeatherEventType::Temperature);
    weatherData.RegisterObserver(0, mockObserver, WeatherEventType::Pressure);

    EXPECT_CALL(mockObserver, Update(testing::_, WeatherEventType::Temperature, testing::_)).Times(1);
    weatherData.SetTemp(22.5);

    EXPECT_CALL(mockObserver, Update(testing::_, WeatherEventType::Pressure, testing::_)).Times(1);
    weatherData.SetPressure(760);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}