#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description);
	std::string GetDescription()const override final;
private:
	std::string m_description;
};

enum class CoffeeSize
{
	Standard,
	Double,
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& coffeeName = "Coffee", CoffeeSize coffeeSize = CoffeeSize::Standard);
	double GetCost() const override;
	std::string GetCoffeeDecription(const std::string& coffeeName, CoffeeSize coffeeSize);
};

// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeeSize coffeeSize);
	double GetCost() const override;
private:
	CoffeeSize m_coffeeSize;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeeSize coffeeSize);
	double GetCost() const override;
private:
	CoffeeSize m_coffeeSize;
};

enum class TeaSort
{
	Black,
	Green,
	White,
	Red,
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaSort sort);
	double GetCost() const override;
	static std::string GetTeaSortDescription(TeaSort sort);
};

enum class MilkshakeSize
{
	Small,
	Medium,
	Big,
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeSize size);
	double GetCost() const override;

	static std::string GetMilkshakeSizeDescription(MilkshakeSize size);
private: 
	MilkshakeSize m_size = MilkshakeSize::Small;
};
