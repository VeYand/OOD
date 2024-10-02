#ifndef COBSERVABLE_H
#define COBSERVABLE_H

#include <unordered_map>
#include <map>
#include "IObservable.h"

// Реализация интерфейса IObservable
template<class T>
class CObservable : public IObservable<T>
{
public:
    typedef IObserver<T> ObserverType;

    void RegisterObserver(unsigned priority, ObserverType &observer) override
    {
        m_observersByPriority.insert({priority, &observer});
        m_observerPriorityMap[&observer] = priority;
    }

    void NotifyObservers() override
    {
        T data = GetChangedData();
        auto observers = m_observersByPriority;
        for (auto &[priority, observer]: observers)
        {
            observer->Update(data, this);
        }
    }

    void RemoveObserver(ObserverType &observer) override
    {
        if (auto observerIt = m_observerPriorityMap.find(&observer); observerIt != m_observerPriorityMap.end())
        {
            auto priority = observerIt->second;
            auto [first, last] = m_observersByPriority.equal_range(priority);

            for (auto observerPriorityIt = first; observerPriorityIt != last; ++observerPriorityIt)
            {
                if (observerPriorityIt->second == &observer)
                {
                    m_observersByPriority.erase(observerPriorityIt);
                    break;
                }
            }
            m_observerPriorityMap.erase(observerIt);
        }
    }

protected:
    // Классы-наследники должны перегрузить данный метод,
    // в котором возвращать информацию об изменениях в объекте
    virtual T GetChangedData() const = 0;

private:
    std::multimap<unsigned, ObserverType *> m_observersByPriority;
    std::unordered_map<ObserverType *, unsigned> m_observerPriorityMap;
};

#endif //COBSERVABLE_H