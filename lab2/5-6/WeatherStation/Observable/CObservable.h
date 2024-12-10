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
	using ObserverType = IObserver<T>;
	using ObserversByPriorityIterator = typename std::multimap<unsigned, ObserverType *>::iterator;

	void RegisterObserver(unsigned priority, ObserverType &observer) override
	{
		auto observerIt = m_observersByPriority.insert({priority, &observer});

		try
		{
			m_observerPriorityMap[&observer] = observerIt;
		}
		catch (...)
		{
			m_observerPriorityMap.erase(&observer);
			throw;
		}
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
		auto observerIt = m_observerPriorityMap.find(&observer);
		if (observerIt != m_observerPriorityMap.end())
		{
			m_observersByPriority.erase(observerIt->second);
			m_observerPriorityMap.erase(observerIt);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::multimap<unsigned, ObserverType *> m_observersByPriority;
	std::unordered_map<ObserverType *, ObserversByPriorityIterator> m_observerPriorityMap;
};

#endif //COBSERVABLE_H
