#include <gtest/gtest.h>
#include "../WeatherStation/Observable/CWeatherData.h"
#include "../WeatherStation/Observer/CDisplay.h"
#include "../WeatherStation/Observer/CStatsDisplay.h"

class SelfRemovingObserver final : public IObserver<SWeatherInfo> {
public:
    explicit SelfRemovingObserver(CObservable<SWeatherInfo> &observable) : m_observable(observable) {
    }

    void Update(SWeatherInfo const &data, IObservable<SWeatherInfo> *observable) override {
        std::cout << "SelfRemovingObserver received update" << std::endl;
        m_observable.RemoveObserver(*this);
    }

private:
    CObservable<SWeatherInfo> &m_observable;
};

class MockObserver final : public IObserver<SWeatherInfo> {
public:
    explicit MockObserver(std::string name) : m_name(std::move(name)) {
    }

    void Update(SWeatherInfo const &data, IObservable<SWeatherInfo> *observable) override {
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

TEST(CObservableTest, SelfRemovingObserverRemovesSelfTest) {
    CWeatherData wd;

    SelfRemovingObserver selfRemovingObserver(wd);
    wd.RegisterObserver(1, selfRemovingObserver);

    CDisplay display;
    wd.RegisterObserver(1, display);

    std::cout << "First change" << std::endl;
    wd.SetMeasurements(3, .7, 760);

    std::cout << "Second change" << std::endl;
    wd.SetMeasurements(-10, .8, 761);
}

TEST(CObservableTest, MultipleSelfRemovingObservers) {
    CWeatherData weatherData;

    SelfRemovingObserver selfRemovingObserver1(weatherData);
    SelfRemovingObserver selfRemovingObserver2(weatherData);

    weatherData.RegisterObserver(1, selfRemovingObserver1);
    weatherData.RegisterObserver(2, selfRemovingObserver2);

    CDisplay display;
    weatherData.RegisterObserver(3, display);

    std::cout << "First change" << std::endl;
    weatherData.SetMeasurements(5, 70, 765);

    std::cout << "Second change" << std::endl;
    weatherData.SetMeasurements(10, 75, 770);
}

TEST(CObservableTest, NotifyObserversWithPriority) {
    CWeatherData weatherData;

    MockObserver observer1("Observer1");
    MockObserver observer2("Observer2");
    MockObserver observer3("Observer3");

    weatherData.RegisterObserver(2, observer2);
    weatherData.RegisterObserver(1, observer1);
    weatherData.RegisterObserver(3, observer3);

    MockObserver::ResetOrder();

    weatherData.SetMeasurements(25, 65, 760);

    const std::vector<std::string> expectedOrder = {"Observer1", "Observer2", "Observer3"};
    ASSERT_EQ(MockObserver::GetOrder(), expectedOrder);
}

TEST(CObservableTest, NotifyObserversWithSamePriority) {
    CWeatherData weatherData;

    MockObserver observer1("Observer1");
    MockObserver observer2("Observer2");
    MockObserver observer3("Observer3");

    weatherData.RegisterObserver(1, observer1);
    weatherData.RegisterObserver(1, observer2);
    weatherData.RegisterObserver(1, observer3);

    MockObserver::ResetOrder();

    weatherData.SetMeasurements(22, 60, 755);

    const std::vector<std::string> expectedOrder = {"Observer1", "Observer2", "Observer3"};
    ASSERT_EQ(MockObserver::GetOrder(), expectedOrder);
}

TEST(CObservableTest, NotifyAfterObserverRemoval) {
    CWeatherData weatherData;

    MockObserver observer1("Observer1");
    MockObserver observer2("Observer2");

    weatherData.RegisterObserver(1, observer1);
    weatherData.RegisterObserver(2, observer2);

    MockObserver::ResetOrder();

    weatherData.SetMeasurements(20, 65, 760);

    std::vector<std::string> expectedOrder = {"Observer1", "Observer2"};
    ASSERT_EQ(MockObserver::GetOrder(), expectedOrder);

    weatherData.RemoveObserver(observer1);

    MockObserver::ResetOrder();

    weatherData.SetMeasurements(30, 70, 765);

    expectedOrder = {"Observer2"};
    ASSERT_EQ(MockObserver::GetOrder(), expectedOrder);
}
