#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template<typename T, typename EventType>
class IObserver;

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template<typename T, typename EventType>
class IObservable
{
public:
	virtual ~IObservable() = default;

	virtual void RegisterObserver(unsigned priority, IObserver<T, EventType> &observer, EventType eventType) = 0;

	virtual void RemoveObserver(IObserver<T, EventType> &observer, EventType eventType) = 0;

protected:
	virtual void NotifyObservers(EventType eventType) = 0;
};

template<typename T, typename EventType>
class IObserver
{
public:
	virtual void Update(T const &data, EventType eventType, IObservable<T, EventType> *observable) = 0;

	virtual ~IObserver() = default;
};

#endif //IOBSERVABLE_H
