#pragma once
#include <string>
#include <memory>
#include <stack>
#include "../task1/Observing.h"

struct SafelyMockData {};
enum class SafelyMockEventType {
	Event,
};

class SafelyMockObservable : public CObservable<SafelyMockData, SafelyMockEventType>
{
public:
	void CallNotifyObservers()
	{
		NotifyObservers(SafelyMockEventType::Event);
	}
protected:
	SafelyMockData GetChangedData(SafelyMockEventType eventType)const override
	{
		return SafelyMockData{};
	}
};

class SafelyMockObserver : public IObserver<SafelyMockData, SafelyMockEventType>
{
public:
	SafelyMockObserver(std::string const& name, std::stack<std::string>& callStack, IObservable<SafelyMockData, SafelyMockEventType>& obsObject)
		: m_name(name),
		m_callStack(&callStack),
		m_obsevableObject(obsObject)
	{}
private:
	void Update(SafelyMockData const& data, SafelyMockEventType eventType, const IObservable<SafelyMockData, SafelyMockEventType>* observablee) override
	{
		m_callStack->push(m_name);
		m_obsevableObject.RemoveObserver(*this, eventType);
	}
	std::stack<std::string>* m_callStack;
	std::string m_name;
	IObservable<SafelyMockData, SafelyMockEventType>& m_obsevableObject;
};