#pragma once
#include <map>
#include <functional>
#include <vector>
#include <stdexcept>

template <typename T, typename E>
class IObservable;

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T, typename E>
class IObserver
{
public:
	virtual void Update(T const& data, E eventType, const IObservable<T, E>* observable) = 0;
	virtual ~IObserver() = default;
};

template <typename T, typename E>
class CObserver : public IObserver<T, E>
{
	struct ObservableRecord
	{
		E eventType;
		IObservable<T, E>* observable;
	};
public:
	~CObserver()
	{
		for (auto& observable : m_observables)
		{
			observable.observable->RemoveObserver(*this, observable.eventType);
		}
	}
	void AddObservable(IObservable<T, E>& observable, E eventType)
	{
		ObservableRecord record;
		record.eventType = eventType;
		record.observable = &observable;
		m_observables.push_back(record);
	}
private:
	std::vector<ObservableRecord> m_observables;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T, typename E>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(CObserver<T, E>& observer, E eventType, int priority) = 0;
	virtual void NotifyObservers(E WeatherChangeEventType) const = 0;
	virtual void RemoveObserver(CObserver<T, E>& observer, E eventType) = 0;
};


// Реализация интерфейса IObservable
template <class T, typename E>
class CObservable : public IObservable<T, E>
{
	typedef CObserver<T, E> ObserverType;
	struct RecordType
	{
		ObserverType* observer;
		int priority;
	};
public:
	void RegisterObserver(ObserverType& observer, E eventType, int priority) override
	{
		std::vector<RecordType>& records = m_observersMap[eventType];
		RecordType rec;
		rec.priority = priority;
		rec.observer = &observer;

		auto iter = records.cbegin();

		while (iter < records.cend())
		{
			RecordType record = *iter;
			if (record.priority < priority)
				break;
			iter++;
		}
		records.insert(iter, rec);

		observer.AddObservable(*this, eventType);
	}

	void NotifyObservers(E eventType)const override
	{
		T data = GetChangedData(eventType);
		try {
			std::vector<RecordType> records = m_observersMap.at(eventType);
			std::vector<ObserverType*> obesrvers;
			for (auto it = records.cbegin(); it != records.cend(); ++it)
			{
				obesrvers.push_back(it->observer);
			}

			for (auto& obesrver : obesrvers)
			{
				obesrver->Update(data, eventType, this);
			}
		}
		catch (std::exception const&) {}
	}

	void RemoveObserver(ObserverType& observer, E eventType) override
	{
		std::vector<RecordType>& records = m_observersMap[eventType];
		for (auto it = records.begin(); it != records.end(); ++it)
		{
			RecordType record = *it;
			if (record.observer == &observer) {
				records.erase(it);
				return;
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData(E eventType)const = 0;

private:
	std::map<E, std::vector<RecordType>> m_observersMap;
};