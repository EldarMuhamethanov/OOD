#pragma once
#include <iostream>

struct QuackBehavior
{
	static void DoQuack() 
	{
		std::cout << "Quack Quack!!!" << std::endl;
	}

	static void DoSqueak() 
	{
		std::cout << "Squeek!!!" << std::endl;
	}

	static void MuteQuack() {}
};