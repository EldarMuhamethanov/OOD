#pragma once
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include "FlyBehavior.h"
#include "QuackBehavior.h"
#include "DanceBehavior.h"

class Duck
{
public:
	Duck(std::unique_ptr<IFlyBehavior>&& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quackBehavior,
		std::unique_ptr<IDanceBehavior>&& danceBehavior)
	{
		SetFlyBehavior(move(flyBehavior));
		SetDanceBehavior(move(danceBehavior));
		SetQuackBehavior(move(quackBehavior));
	}
	void Quack() const
	{
		m_quackBehavior->Quack();
	}
	void Swim() const
	{
		std::cout << "I'm swimming" << std::endl;
	}
	void Fly() const
	{
		m_flyBehavior->Fly();
	}
	virtual void Dance() const
	{
		m_danceBehavior->Dance();
	}
	void SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = std::move(flyBehavior);
	}
	void SetQuackBehavior(std::unique_ptr<IQuackBehavior>&& quackBehavior)
	{
		assert(quackBehavior);
		m_quackBehavior = std::move(quackBehavior);
	}
	void SetDanceBehavior(std::unique_ptr<IDanceBehavior>&& danceBehavior)
	{
		assert(danceBehavior);
		m_danceBehavior = std::move(danceBehavior);
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(std::make_unique<FlyWithWings>(), std::make_unique<QuackBehavior>(), std::make_unique<DanceWaltz>())
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
		: Duck(std::make_unique<FlyWithWings>(), std::make_unique<QuackBehavior>(), std::make_unique<DanceMinuet>())
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
		: Duck(std::make_unique<FlyNoWay>(), std::make_unique<MuteQuackBehavior>(), std::make_unique<NoDande>())
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
		: Duck(std::make_unique<FlyNoWay>(), std::make_unique<SqueakBehavior>(), std::make_unique<NoDande>())
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
		: Duck(std::make_unique<FlyNoWay>(), std::make_unique<QuackBehavior>(), std::make_unique<NoDande>())
	{
	}
	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};