#include "Beverages.h"
#include <stdexcept>

using namespace std;

CBeverage::CBeverage(const string& description) : m_description(description) {}
string CBeverage::GetDescription()const
{
	return m_description;
}

CCoffee::CCoffee(const string& coffeeName, CoffeeSize coffeeSize)
	: CBeverage(GetCoffeeDecription(coffeeName, coffeeSize))
{}

double CCoffee::GetCost() const
{
	return 60;
}

string CCoffee::GetCoffeeDecription(const string& coffeeName, CoffeeSize coffeeSize)
{
	string size = "";
	switch (coffeeSize)
	{
	case CoffeeSize::Standard:
		size = "standard";
		break;
	case CoffeeSize::Double:
		size = "double";
		break;
	default:
		throw invalid_argument("invalid coffe size");
	}
	return size + " " + coffeeName;
}


CCappuccino::CCappuccino(CoffeeSize coffeeSize)
	: CCoffee("Cappuccino", coffeeSize)
	, m_coffeeSize(coffeeSize)
{}

double CCappuccino::GetCost() const
{
	switch (m_coffeeSize)
	{
	case CoffeeSize::Standard:
		return 80;
	case CoffeeSize::Double:
		return 120;
	default:
		throw invalid_argument("invalid size of cappuccino");
		break;
	}
}

CLatte::CLatte(CoffeeSize coffeeSize) 
	: CCoffee("Latte", coffeeSize)
	, m_coffeeSize(coffeeSize)
{}

double CLatte::GetCost() const
{
	switch (m_coffeeSize)
	{
	case CoffeeSize::Standard:
		return 90;
	case CoffeeSize::Double:
		return 130;
	default:
		throw invalid_argument("invalid size of latte");
		break;
	}
}

string CTea::GetTeaSortDescription(TeaSort sort)
{
	switch (sort)
	{
	case TeaSort::Black:
		return "black tea";
	case TeaSort::Green:
		return "green tea";
	case TeaSort::White:
		return "white tea";
	case TeaSort::Red:
		return "red tea";
	default:
		return "";
	}
}

CTea::CTea(TeaSort sort) : CBeverage(GetTeaSortDescription(sort)) {}

double CTea::GetCost() const
{
	return 30;
}

string CMilkshake::GetMilkshakeSizeDescription(MilkshakeSize size)
{
	switch (size)
	{
	case MilkshakeSize::Small:
		return "small Milkshake";
	case MilkshakeSize::Medium:
		return "medium Milkshake";
	case MilkshakeSize::Big:
		return "big Milkshake";
	default:
		return "";
	}
}

CMilkshake::CMilkshake(MilkshakeSize size) 
	: m_size(size),
	CBeverage(GetMilkshakeSizeDescription(size)) 
{}
double CMilkshake::GetCost() const
{
	switch (m_size)
	{
	case MilkshakeSize::Small:
		return 50;
	case MilkshakeSize::Medium:
		return 60;
	case MilkshakeSize::Big:
		return 80;
	default:
		throw invalid_argument("invalid size of milkshake");
	}
}