#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../State/GumballMachineWithState.h"
#include "../State/NaiveGumballMachine.h"
#include <functional>
#include <sstream>

using namespace std;

void CallFnWithCheck(function<void()> const& fn, string const& result)
{
	string out;
	ostringstream outStream(out);
	streambuf* coutbuf = cout.rdbuf();
	cout.rdbuf(outStream.rdbuf());

	fn();

	cout.rdbuf(coutbuf);
	REQUIRE(outStream.str() == result);
}

string CreateStateString(unsigned ballsCount, unsigned quartersCount, string state)
{
	std::string fmt = "Mighty Gumball, Inc."
		"C++ - enabled Standing Gumball Model #2016 (with state)"
		"Inventory: " + std::to_string(ballsCount) + " gumball " + (ballsCount!= 1 ? "s" : "") + " "
		"Quarters: " + std::to_string(quartersCount) + " quarters " + (quartersCount!= 1 ? "s" : "") + " "
		"Machine is " + state;

	return fmt;
}

template <typename GumballMachineType>
void InsertQuarter(GumballMachineType& machine, string expectedMessage)
{
	CallFnWithCheck([&machine]() { machine.InsertQuarter(); }, expectedMessage);
}

template <typename GumballMachineType>
void TurnCrank(GumballMachineType& machine, string expectedMessage)
{
	CallFnWithCheck([&machine]() { machine.TurnCrank(); }, expectedMessage);
}

template <typename GumballMachineType>
void EjectQuarters(GumballMachineType& machine, string expectedMessage)
{
	CallFnWithCheck([&machine]() { machine.EjectQuarters(); }, expectedMessage);
}

template <typename GumballMachineType>
void Refill(GumballMachineType& machine, unsigned count, string expectedMessage)
{
	CallFnWithCheck([&machine, count]() { machine.Refill(count); }, expectedMessage);
}

template <typename GumballMachineType>
void TestGumballMachine(GumballMachineType& machine)
{
	REQUIRE(machine.ToString() == CreateStateString(3, 0, "waiting for quarter"));
	EjectQuarters(machine, "You haven't inserted a quarter\n");
	TurnCrank(machine, "You turned but there's no quarter\nYou need to pay first\n");

	WHEN("insert quarter")
	{
		InsertQuarter(machine, "You inserted a quarter\n");
		REQUIRE(machine.ToString() == CreateStateString(3, 1, "waiting for turn of crank"));
		THEN("turn of cranck")
		{
			TurnCrank(machine, "You turned...\nA gumball comes rolling out the slot...\n");
			REQUIRE(machine.ToString() == CreateStateString(2, 0, "waiting for quarter"));
		}
		THEN("eject quarters")
		{
			EjectQuarters(machine, "Quarters returned\n");
			REQUIRE(machine.ToString() == CreateStateString(3, 0, "waiting for quarter"));
		}
	}
	WHEN("insert max amount of quarter and then eject it")
	{
		InsertQuarter(machine, "You inserted a quarter\n");
		InsertQuarter(machine, "Insert one more Quarter\n");
		InsertQuarter(machine, "Insert one more Quarter\n");
		InsertQuarter(machine, "Insert one more Quarter\n");
		InsertQuarter(machine, "Insert one more Quarter\n");
		REQUIRE(machine.ToString() == CreateStateString(3, 5, "waiting for turn of crank"));
		WHEN("insert 6th quarter")
		{
			InsertQuarter(machine, "Cant Insert quarters, Amount of quarters is max\n");
			REQUIRE(machine.ToString() == CreateStateString(3, 5, "waiting for turn of crank"));
		}
		WHEN("eject quarters")
		{
			EjectQuarters(machine, "Quarters returned\n");
			REQUIRE(machine.ToString() == CreateStateString(3, 0, "waiting for quarter"));
		}
		WHEN("buy all gumballs")
		{
			TurnCrank(machine, "You turned...\nA gumball comes rolling out the slot...\n");
			TurnCrank(machine, "You turned...\nA gumball comes rolling out the slot...\n");
			TurnCrank(machine, "You turned...\nA gumball comes rolling out the slot...\n");
			REQUIRE(machine.ToString() == CreateStateString(0, 2, "sold out"));
			TurnCrank(machine, "You turned but there's no gumballs\nNo gumball dispensed\n");
			REQUIRE(machine.ToString() == CreateStateString(0, 2, "sold out"));
			InsertQuarter(machine, "You can't insert a quarter, the machine is sold out\n");
			REQUIRE(machine.ToString() == CreateStateString(0, 2, "sold out"));
			THEN("eject quarters")
			{
				EjectQuarters(machine, "Return quarters\n");
				REQUIRE(machine.ToString() == CreateStateString(0, 0, "sold out"));
			}
		}
	}
	WHEN("inserts quarters")
	{
		InsertQuarter(machine, "You inserted a quarter\n");
		InsertQuarter(machine, "Insert one more Quarter\n");
		InsertQuarter(machine, "Insert one more Quarter\n");
		REQUIRE(machine.ToString() == CreateStateString(3, 3, "waiting for turn of crank"));
		WHEN("buy gumball")
		{
			TurnCrank(machine, "You turned...\nA gumball comes rolling out the slot...\n");
			REQUIRE(machine.ToString() == CreateStateString(2, 2, "waiting for turn of crank"));

			WHEN("Insert one more quarter")
			{
				InsertQuarter(machine, "Insert one more Quarter\n");
				REQUIRE(machine.ToString() == CreateStateString(2, 3, "waiting for turn of crank"));
			}
		}
	}
}

SCENARIO("GumballMachine test with State")
{
	with_state::CGumballMachine machine(3);
	TestGumballMachine(machine);
}

SCENARIO("GumballMachine test naive realization")
{
	naive::CGumballMachine machine(3);
	TestGumballMachine(machine);
}

SCENARIO("Test refill method")
{
	with_state::CGumballMachine machine(0);

	WHEN("sold out")
	{
		Refill(machine, 1, "Add Gum balls in gumballMachine\n");
		WHEN("no quarters")
		{
			Refill(machine, 1, "Add Gum balls in gumballMachine\n");
			REQUIRE(machine.ToString() == CreateStateString(2, 0, "waiting for quarter"));

			InsertQuarter(machine, "You inserted a quarter\n");
			InsertQuarter(machine, "Insert one more Quarter\n");
			InsertQuarter(machine, "Insert one more Quarter\n");

			WHEN("Has quarter")
			{
				Refill(machine, 1, "Add Gum balls in gumballMachine\n");
				REQUIRE(machine.ToString() == CreateStateString(3, 3, "waiting for turn of crank"));
				InsertQuarter(machine, "Insert one more Quarter\n");
				InsertQuarter(machine, "Insert one more Quarter\n");

				WHEN("Has max quarters")
				{
					Refill(machine, 1, "Add Gum balls in gumballMachine\n");
					REQUIRE(machine.ToString() == CreateStateString(4, 5, "waiting for turn of crank"));
					TurnCrank(machine, "You turned...\nA gumball comes rolling out the slot...\n");
					REQUIRE(machine.ToString() == CreateStateString(3, 4, "waiting for turn of crank"));
					Refill(machine, 2, "Add Gum balls in gumballMachine\n");
					REQUIRE(machine.ToString() == CreateStateString(5, 4, "waiting for turn of crank"));
				}
			}
		}
	}
}