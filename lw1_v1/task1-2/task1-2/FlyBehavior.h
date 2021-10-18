#pragma once
#include <iostream>

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};

class FlyBehavior : public IFlyBehavior
{
public:
	void IncFlyCount()
	{
		++m_fliesCount;
	}
	int GetFlyCount() const
	{
		return m_fliesCount;
	}
private:
	int m_fliesCount = 0;
};

class FlyWithWings : public FlyBehavior
{
public:
	void Fly() override
	{
		IncFlyCount();
		std::cout << "I'm flying with wings " << GetFlyCount() << " times!!" << std::endl;
	}
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override {}
};