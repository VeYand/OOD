#ifndef IOBSERVABLE_H
#define IOBSERVABLE_H

#include "../Observable/IObservable.h"

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template<typename T>
class IObserver;

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template<typename T>
class IObservable
{
public:
    virtual ~IObservable() = default;

    virtual void RegisterObserver(unsigned priority, IObserver<T> &observer) = 0;

    virtual void NotifyObservers() = 0;

    virtual void RemoveObserver(IObserver<T> &observer) = 0;
};

template<typename T>
class IObserver
{
public:
    virtual void Update(T const &data) = 0;

    virtual ~IObserver() = default;
};

#endif //IOBSERVABLE_H
