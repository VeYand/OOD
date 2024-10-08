#ifndef COBSERVABLE_H
#define COBSERVABLE_H
#include <set>

#include "IObservable.h"

// Реализация интерфейса IObservable
template<class T>
class CObservable : public IObservable<T>
{
public:
    typedef IObserver<T> ObserverType;

    void RegisterObserver(ObserverType &observer) override
    {
        m_observers.insert(&observer);
    }

    void NotifyObservers() override
    {
        T data = GetChangedData();
        auto observers = m_observers; // TODO Что если Observer деструктуризируетсся раньше чем субъект?
        for (auto &observer: observers)
        {
            observer->Update(data);
        }
    }

    void RemoveObserver(ObserverType &observer) override
    {
        m_observers.erase(&observer);
    }

protected:
    // Классы-наследники должны перегрузить данный метод,
    // в котором возвращать информацию об изменениях в объекте
    virtual T GetChangedData() const = 0;

private:
    std::set<ObserverType *> m_observers;
};

#endif //COBSERVABLE_H
