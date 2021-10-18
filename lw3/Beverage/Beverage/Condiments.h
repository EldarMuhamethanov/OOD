#pragma once

#include "IBeverage.h"
#include <stdexcept>

// Базовый декоратор "Добавка к напитку". Также является напитком
class CCondimentDecorator : public IBeverage
{
public:
	std::string GetDescription()const override;

	double GetCost()const override;

	// Стоимость и описание добавки вычисляется в классах конкретных декораторов
	virtual std::string GetCondimentDescription()const = 0;
	virtual double GetCondimentCost()const = 0;
protected:
	CCondimentDecorator(IBeveragePtr&& beverage);
private:
	IBeveragePtr m_beverage;
};

// Добавка из корицы
class CCinnamon : public CCondimentDecorator
{
public:
	CCinnamon(IBeveragePtr&& beverage);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
};


// Лимонная добавка
class CLemon : public CCondimentDecorator
{
public:
	CLemon(IBeveragePtr&& beverage, unsigned quantity = 1);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	unsigned m_quantity;
};


enum class IceCubeType
{
	Dry,	// Сухой лед (для суровых сибирских мужиков)
	Water	// Обычные кубики из воды
};

// Добавка "Кубики льда". Определяется типом и количеством кубиков, что влияет на стоимость
// и описание
class CIceCubes : public CCondimentDecorator
{
public:
	CIceCubes(IBeveragePtr&& beverage, unsigned quantity, IceCubeType type = IceCubeType::Water);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	unsigned m_quantity;
	IceCubeType m_type;
};



// Тип сиропа
enum class SyrupType
{
	Chocolate,	// Шоколадный
	Maple,		// Кленовый
};

// Добавка "Сироп"
class CSyrup : public CCondimentDecorator
{
public:
	CSyrup(IBeveragePtr&& beverage, SyrupType syrupType);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	SyrupType m_syrupType;
};



// Шоколадная крошка
class CChocolateCrumbs : public CCondimentDecorator
{
public:
	CChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	unsigned m_mass;
};

// Кокосовая стружка
class CCoconutFlakes : public CCondimentDecorator
{
public:
	CCoconutFlakes(IBeveragePtr&& beverage, unsigned mass);

protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	unsigned m_mass;
};

class CCream : public CCondimentDecorator
{
public:
	CCream(IBeveragePtr&& beverage);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
};

class CSliceOfChocolate  : public CCondimentDecorator
{
public:
	CSliceOfChocolate(IBeveragePtr&& beverage, unsigned quantity = 1);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	unsigned m_quantity;
};


enum class LiquorType
{
	Walnut,
	Chocolate,
};

class CLiquor : public CCondimentDecorator
{
public:
	CLiquor(IBeveragePtr&& beverage, LiquorType liquorType);
protected:
	double GetCondimentCost()const override;
	std::string GetCondimentDescription()const override;
private:
	LiquorType m_liquorType;
};