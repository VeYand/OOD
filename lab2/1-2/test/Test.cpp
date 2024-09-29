#include <gtest/gtest.h>
#include "../WeatherStation/Model/SWeatherInfo.h"
#include "../WeatherStation/Observable/CObservable.h"
#include "../WeatherStation/Observable/CWeatherData.h"
#include "../WeatherStation/Observer/CDisplay.h"

class SelfRemovingObserver final : public IObserver<SWeatherInfo> {
public:
    explicit SelfRemovingObserver(CObservable<SWeatherInfo> &observable) : m_observable(observable) {
    }

    void Update(SWeatherInfo const &data) override {
        std::cout << "SelfRemovingObserver received update" << std::endl;
        std::cout << "----------------" << std::endl;
        m_observable.RemoveObserver(*this);
    }

private:
    CObservable<SWeatherInfo> &m_observable;
};

TEST(CObservableTest, SelfRemovingObserverRemovesSelfTest) {
    CWeatherData wd;

    SelfRemovingObserver selfRemovingObserver(wd);
    wd.RegisterObserver(selfRemovingObserver);

    CDisplay display;
    wd.RegisterObserver(display);

    std::cout << "First change" << std::endl;
    wd.SetMeasurements(3, 0.7, 760);

    std::cout << "Second change" << std::endl;
    wd.SetMeasurements(-10, 0.8, 761);
}

TEST(CObservableTest, MultipleSelfRemovingObservers) {
    CWeatherData weatherData;

    SelfRemovingObserver selfRemovingObserver1(weatherData);
    SelfRemovingObserver selfRemovingObserver2(weatherData);

    weatherData.RegisterObserver(selfRemovingObserver1);
    weatherData.RegisterObserver(selfRemovingObserver2);

    CDisplay display;
    weatherData.RegisterObserver(display);

    std::cout << "First change" << std::endl;
    weatherData.SetMeasurements(5, 70, 765);

    std::cout << "Second change" << std::endl;
    weatherData.SetMeasurements(10, 75, 770);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
