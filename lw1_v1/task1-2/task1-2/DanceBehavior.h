#pragma once
#include <iostream>

struct IDanceBehavior
{
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};
class DanceWaltz : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "Dance Waltz" << std::endl;
	}
};

class DanceMinuet : public IDanceBehavior
{
public:
	void Dance() override
	{
		std::cout << "Dance Minuet" << std::endl;
	}
};

class NoDande : public IDanceBehavior
{
public:
	void Dance() override {}
};