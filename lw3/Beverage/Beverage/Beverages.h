#pragma once

#include "IBeverage.h"

// ������� ���������� �������, ��������������� ��� ��������
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

// ����
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& coffeeName = "Coffee", CoffeeSize coffeeSize = CoffeeSize::Standard);
	double GetCost() const override;
	std::string GetCoffeeDecription(const std::string& coffeeName, CoffeeSize coffeeSize);
};

// ���������
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeeSize coffeeSize);
	double GetCost() const override;
private:
	CoffeeSize m_coffeeSize;
};

// �����
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

// ���
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

// �������� ��������
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakeSize size);
	double GetCost() const override;

	static std::string GetMilkshakeSizeDescription(MilkshakeSize size);
private: 
	MilkshakeSize m_size = MilkshakeSize::Small;
};
