#ifndef COBSERVABLE_H
#define COBSERVABLE_H

#include <boost/signals2.hpp>
#include "IObservable.h"

template<typename T, typename EventType>
class CObservable : public IObservable<T, EventType>
{
public:
	using ObserverSlot = std::function<void(const T &, EventType)>;

	void RegisterObserver(unsigned priority, IObserver<T, EventType> &observer, EventType eventType) override
	{
		auto &signal = m_signals[eventType];
		auto connection = signal.connect(priority, [&observer](const T &data, EventType eventType) {
			observer.Update(data, eventType, nullptr);
		});
		m_connections[&observer][eventType] = connection;
	}

	void RemoveObserver(IObserver<T, EventType> &observer, EventType eventType) override
	{
		auto observerIt = m_connections.find(&observer);
		if (observerIt != m_connections.end())
		{
			auto eventIt = observerIt->second.find(eventType);
			if (eventIt != observerIt->second.end())
			{
				eventIt->second.disconnect();
				observerIt->second.erase(eventIt);
			}
			if (observerIt->second.empty())
			{
				m_connections.erase(observerIt);
			}
		}
	}

protected:
	void NotifyObservers(EventType eventType) override
	{
		T data = GetChangedData();
		if (m_signals.contains(eventType))
		{
			m_signals[eventType](data, eventType);
		}
	}

	virtual T GetChangedData() const = 0;

private:
	std::map<EventType, boost::signals2::signal<void(const T &, EventType)> > m_signals;
	std::map<IObserver<T, EventType> *, std::map<EventType, boost::signals2::connection> > m_connections;
};

#endif // COBSERVABLE_H
