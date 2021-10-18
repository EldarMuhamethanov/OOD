#include "Beverages.h"
#include "Condiments.h"
#include <iostream>

using namespace std;

int main()
{
	//CTea teaSort(TeaSort::Black);
	//cout << "tea description " << teaSort.GetDescription() << endl;
	//cout << "tea cost " << teaSort.GetCost() << endl;

	//CCappuccino cappuccino(CoffeeSize::Double);
	//cout << "cappuccino description " << cappuccino.GetDescription() << endl;
	//cout << "cappuccino cost " << cappuccino.GetCost() << endl;

	//CCappuccino latte(CoffeeSize::Double);
	//cout << "latte description " << latte.GetDescription() << endl;
	//cout << "latte cost " << latte.GetCost() << endl;

	//CMilkshake milkshake(MilkshakeSize::Big);
	//cout << "milkshake description " << milkshake.GetDescription() << endl;
	//cout << "milkshake cost " << milkshake.GetCost() << endl;

	// �������� ������� �����
	auto latte = make_unique<CLatte>(CoffeeSize::Double);
	// ��������� ������
	auto cinnamon = make_unique<CCinnamon>(move(latte));
	// ��������� ���� ����� ������
	auto lemon = make_unique<CLemon>(move(cinnamon), 2);
	// ��������� ���� ������� ����
	auto iceCubes = make_unique<CIceCubes>(move(lemon), 2, IceCubeType::Dry);
	auto cream = make_unique<CCream>(move(iceCubes));
	auto sliceOfChocolate = make_unique<CSliceOfChocolate>(move(cream), 5);
	auto liquor = make_unique<CLiquor>(move(sliceOfChocolate), LiquorType::Walnut);
	// ��������� 2 ������ ���������� ������
	auto beverage = make_unique<CChocolateCrumbs>(move(liquor), 2);

	// ���������� ���� ����������
	cout << beverage->GetDescription() << " costs " << beverage->GetCost() << endl;

	return 0;
}