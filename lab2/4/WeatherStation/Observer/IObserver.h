#ifndef IOBSERVER_H
#define IOBSERVER_H

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template<typename T>
class IObservable;

template<typename T> // todo перенсети в Observable
class IObserver
{
public:
    virtual void Update(T const &data, IObservable<T> *observable) = 0;

    virtual ~IObserver() = default;
};

#endif //IOBSERVER_H
