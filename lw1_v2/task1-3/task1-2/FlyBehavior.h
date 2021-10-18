#pragma once
#include <functional>
#include <iostream>

struct FlyBehavior
{
	static std::function<void()> FlyWithWingsDecorator() 
	{
		int counter = 0;

		return [counter]() mutable -> void {
			++counter;
			std::cout << "I'm flying with wing " << counter << " times!!!" << std::endl;
		};
	}

	static void FlyNoWay() {}
};