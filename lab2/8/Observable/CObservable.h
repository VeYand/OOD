#ifndef COBSERVABLE_H
#define COBSERVABLE_H

#include <unordered_set>
#include <map>
#include "IObservable.h"

// Реализация интерфейса IObservable
template<class T, class EventType>
class CObservable : public IObservable<T, EventType>
{
public:
	using ObserverType = IObserver<T, EventType>;
	using ObserversByPriorityIterator = typename std::multimap<unsigned, ObserverType *>::iterator;

	void RegisterObserver(unsigned priority, ObserverType &observer, EventType eventType) override
	{
		if (!m_observers.contains(eventType))
		{
			m_observers.insert({eventType, {}});
		}
		if (!m_observers.at(eventType).contains(priority))
		{
			m_observers.at(eventType).insert({priority, {}});
		}

		m_observers.at(eventType).at(priority).insert(&observer);
	}

	void RemoveObserver(ObserverType &observer, EventType eventType) override
	{
		for (auto &[priority, observers]: m_observers[eventType])
		{
			if (observers.erase(&observer))
			{
				return;
			}
		}
	}

protected:
	void NotifyObservers(EventType eventType) override
	{
		T data = GetChangedData();
		auto observersCopy = m_observers;
		for (auto &[priority, observers]: m_observers[eventType])
		{
			for (auto &observer: observers)
			{
				observer->Update(data, eventType);
			}
		}
	}

	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::map<EventType, std::map<int, std::unordered_set<ObserverType *> > > m_observers;
};


#endif //COBSERVABLE_H
