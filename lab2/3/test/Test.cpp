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

TEST(ObserverTest, SelfRemovingObserverRemovesSelfTest) {
    CWeatherData wd;

    SelfRemovingObserver selfRemovingObserver(wd);
    wd.RegisterObserver(1, selfRemovingObserver);

    CDisplay display;
    wd.RegisterObserver(1, display);

    std::cout << "First change" << std::endl;
    wd.SetMeasurements(3, 0.7, 760);

    std::cout << "Second change" << std::endl;
    wd.SetMeasurements(-10, 0.8, 761);
}

class MockObserver : public IObserver<SWeatherInfo> {
public:
    explicit MockObserver(std::string name) : m_name(std::move(name)) {}

    void Update(SWeatherInfo const &data) override {
        m_order.push_back(m_name);
    }

    static void ResetOrder() {
        m_order.clear();
    }

    static std::vector<std::string> GetOrder() {
        return m_order;
    }

private:
    std::string m_name;
    static std::vector<std::string> m_order;
};

std::vector<std::string> MockObserver::m_order = {};

TEST(CObservableTest, NotifyObserversWithPriority) {
    CWeatherData weatherData;

    MockObserver observer1("Observer1");
    MockObserver observer2("Observer2");
    MockObserver observer3("Observer3");

    weatherData.RegisterObserver(2, observer2);
    weatherData.RegisterObserver(1, observer1);
    weatherData.RegisterObserver(3, observer3);

    MockObserver::ResetOrder();

    weatherData.SetMeasurements(25.0, 65.0, 760.0);

    std::vector<std::string> expectedOrder = {"Observer1", "Observer2", "Observer3"};
    ASSERT_EQ(MockObserver::GetOrder(), expectedOrder);
}

GTEST_API_ int main(int argc, char **argv) {
    std::cout << "Running tests" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
