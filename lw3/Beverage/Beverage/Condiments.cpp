#include "Condiments.h"


using namespace std;

CCondimentDecorator::CCondimentDecorator(IBeveragePtr&& beverage) : m_beverage(move(beverage)) {}
string CCondimentDecorator::GetDescription()const
{
	// Описание декорированного напитка добавляется к описанию оборачиваемого напитка
	return m_beverage->GetDescription() + ", " + GetCondimentDescription();
}
double CCondimentDecorator::GetCost()const
{
	// Стоимость складывается из стоимости добавки и стоимости декорируемого напитка
	return m_beverage->GetCost() + GetCondimentCost();
}


CCinnamon::CCinnamon(IBeveragePtr&& beverage) : CCondimentDecorator(move(beverage)) {}
double CCinnamon::GetCondimentCost()const
{
	return 20;
}
string CCinnamon::GetCondimentDescription()const
{
	return "Cinnamon";
}


CLemon::CLemon(IBeveragePtr&& beverage, unsigned quantity)
	: CCondimentDecorator(move(beverage))
	, m_quantity(quantity)
{}
double CLemon::GetCondimentCost()const
{
	return 10.0 * m_quantity;
}
string CLemon::GetCondimentDescription()const
{
	return "Lemon x " + to_string(m_quantity);
}


CIceCubes::CIceCubes(IBeveragePtr&& beverage, unsigned quantity, IceCubeType type)
	: CCondimentDecorator(move(beverage))
	, m_quantity(quantity)
	, m_type(type)
{}
double CIceCubes::GetCondimentCost()const
{
	// Чем больше кубиков, тем больше стоимость.
	// Сухой лед стоит дороже
	return (m_type == IceCubeType::Dry ? 10 : 5) * m_quantity;
}
string CIceCubes::GetCondimentDescription()const
{
	return string(m_type == IceCubeType::Dry ? "Dry" : "Water")
		+ " ice cubes x " + to_string(m_quantity);
}


CSyrup::CSyrup(IBeveragePtr&& beverage, SyrupType syrupType)
	: CCondimentDecorator(move(beverage))
	, m_syrupType(syrupType)
{}
double CSyrup::GetCondimentCost()const
{
	return 15;
}
string CSyrup::GetCondimentDescription()const
{
	return string(m_syrupType == SyrupType::Chocolate ? "Chocolate" : "Maple") + " syrup";
}


CChocolateCrumbs::CChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass)
	:CCondimentDecorator(move(beverage))
	, m_mass(mass)
{}
double CChocolateCrumbs::GetCondimentCost()const
{
	return 2.0 * m_mass;
}
string CChocolateCrumbs::GetCondimentDescription()const
{
	return "Chocolate crumbs " + to_string(m_mass) + "g";
}


CCoconutFlakes::CCoconutFlakes(IBeveragePtr&& beverage, unsigned mass)
	: CCondimentDecorator(move(beverage))
	, m_mass(mass)
{}
double CCoconutFlakes::GetCondimentCost()const
{
	return 1.0 * m_mass;
}
string CCoconutFlakes::GetCondimentDescription()const
{
	return "Coconut flakes " + to_string(m_mass) + "g";
}


CCream::CCream(IBeveragePtr&& beverage) : CCondimentDecorator(move(beverage)) {};
double CCream::GetCondimentCost()const
{
	return 25;
}
string CCream::GetCondimentDescription()const
{
	return "Cream";
}

CSliceOfChocolate::CSliceOfChocolate(IBeveragePtr&& beverage, unsigned quantity)
	: CCondimentDecorator(move(beverage))
{
	if (quantity > 5) {
		throw invalid_argument("invalid quantity of slice of chocolate " + to_string(quantity));
	}
	m_quantity = quantity;
};
double CSliceOfChocolate::GetCondimentCost()const
{
	return m_quantity * 10;
}
string CSliceOfChocolate::GetCondimentDescription() const
{
	return "slide of chocolate x " + to_string(m_quantity);
}


CLiquor::CLiquor(IBeveragePtr&& beverage, LiquorType liquorType)
	: CCondimentDecorator(move(beverage))
	, m_liquorType(liquorType)
{}
double CLiquor::GetCondimentCost()const
{
	return 50;
}
string CLiquor::GetCondimentDescription() const
{
	return string(m_liquorType == LiquorType::Chocolate ? "Chocolate" : "Walnut") + " liquor";
}