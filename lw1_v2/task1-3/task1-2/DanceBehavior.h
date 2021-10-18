#pragma once
#include <iostream>

struct DanceBehavior
{
	static void DanceWaltz() 
	{
		std::cout << "dance waltz" << std::endl;
	};
	static void DanceMinuet()
	{
		std::cout << "dance minuet" << std::endl;
	};
	static void NoDance() {};
};
