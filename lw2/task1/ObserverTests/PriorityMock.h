#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <stack>
#include "../task1/Observing.h"

struct MockData {};

enum class PriorityMockEventType {
	Event,
};

class PriorityMockObservable: public CObservable<MockData, PriorityMockEventType>
{
public:
	void CallNotifyObservers()
	{
		NotifyObservers(PriorityMockEventType::Event);
	}
protected:
	MockData GetChangedData(PriorityMockEventType eventType)const override
	{
		return MockData{};
	}
};

class PriorityMockObserver: public IObserver<MockData, PriorityMockEventType>
{
public:
	PriorityMockObserver(std::string const& name, std::stack<std::string>& callStack): m_name(name), m_callStack(&callStack) {}
private:
	void Update(MockData const& data, PriorityMockEventType eventType, const IObservable<MockData, PriorityMockEventType>* observablee) override
	{
		m_callStack->push(m_name);
	}
private:
	std::stack<std::string>* m_callStack;
	std::string m_name;
};