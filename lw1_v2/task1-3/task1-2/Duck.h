#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "DanceBehavior.h"

typedef std::function<void()> ActionCallback;

class Duck
{
public:
	Duck(ActionCallback flyBehavior,
		ActionCallback quackBehavior,
		ActionCallback danceBehavior)
	{
		SetDanceBehavior(danceBehavior);
		SetFlyBehavior(flyBehavior);
		SetQuackBehavior(quackBehavior);
	}
	void Quack() const
	{
		m_quackBehavior();
	}
	void Swim() const
	{
		std::cout << "I'm swimming" << std::endl;
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance() const
	{
		std::cout << "I'm Dancing" << std::endl;
	}
	void SetDanceBehavior(ActionCallback danceBehavior)
	{
		m_danceBehavior = danceBehavior;
	}
	void SetFlyBehavior(ActionCallback flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	void SetQuackBehavior(ActionCallback quackBehavior)
	{
		m_quackBehavior = quackBehavior;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	ActionCallback m_flyBehavior;
	ActionCallback m_quackBehavior;
	ActionCallback m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyBehavior::FlyWithWingsDecorator(), QuackBehavior::DoQuack, DanceBehavior::DanceWaltz)
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyBehavior::FlyWithWingsDecorator(), QuackBehavior::DoQuack, DanceBehavior::DanceMinuet)
	{
	}
	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyBehavior::FlyNoWay, QuackBehavior::MuteQuack, DanceBehavior::NoDance)
	{
	}
	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyBehavior::FlyNoWay, QuackBehavior::DoSqueak, DanceBehavior::NoDance)
	{
	}
	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyBehavior::FlyNoWay, QuackBehavior::DoQuack, DanceBehavior::NoDance)
	{
	}
	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};