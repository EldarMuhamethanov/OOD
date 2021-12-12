#pragma once
#include <iostream>
#include <string>

namespace naive
{
	const unsigned MAX_QUARTERS_COUNT = 5;
	class CGumballMachine
	{
	public:
		enum class State
		{
			SoldOut,		// Жвачка закончилась
			NoQuarter,		// Нет монетки
			HasQuarters,	// Есть монетка
			Sold,			// жвачка выдана
		};

		CGumballMachine(unsigned count)
			: m_count(count)
			, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
		{
		}

		void InsertQuarter()
		{
			switch (m_state)
			{
			case State::SoldOut:
				std::cout << "You can't insert a quarter, the machine is sold out\n";
				break;
			case State::NoQuarter:
				std::cout << "You inserted a quarter\n";
				++m_quartersCount;
				m_state = State::HasQuarters;
				break;
			case State::HasQuarters:
				if (m_quartersCount == MAX_QUARTERS_COUNT)
				{
					std::cout << "Cant Insert quarters, Amount of quarters is max\n";
					return;
				}
				++m_quartersCount;
				std::cout << "Insert one more Quarter\n";
				break;
			case State::Sold:
				std::cout << "Please wait, we're already giving you a gumball\n";
				break;
			}
		}

		void EjectQuarters()
		{
			switch (m_state)
			{
			case State::NoQuarter:
				std::cout << "You haven't inserted a quarter\n";
				break;
			case State::HasQuarters:
				std::cout << "Quarters returned\n";
				m_quartersCount = 0;
				m_state = State::NoQuarter;
				break;
			case State::Sold:
				std::cout << "Sorry you already turned the crank\n";
				break;
			case State::SoldOut:
				std::cout << "Return quarters\n";
				m_quartersCount = 0;
				break;
			}
		}

		void TurnCrank()
		{
			switch (m_state)
			{
			case State::SoldOut:
				std::cout << "You turned but there's no gumballs\n";
				break;
			case State::NoQuarter:
				std::cout << "You turned but there's no quarter\n";
				break;
			case State::HasQuarters:
				std::cout << "You turned...\n";
				m_state = State::Sold;
				break;
			case State::Sold:
				std::cout << "Turning twice doesn't get you another gumball\n";
				break;
			}
			Dispense();
		}

		std::string ToString()const
		{
			std::string state =
				(m_state == State::SoldOut) ? "sold out" :
				(m_state == State::NoQuarter) ? "waiting for quarter" :
				(m_state == State::HasQuarters) ? "waiting for turn of crank"
				: "delivering a gumball";
			std::string fmt = "Mighty Gumball, Inc."
				"C++ - enabled Standing Gumball Model #2016 (with state)"
				"Inventory: " + std::to_string(m_count) + " gumball " + (m_count != 1 ? "s" : "") + " "
				"Quarters: " + std::to_string(m_quartersCount) + " quarters " + (m_quartersCount != 1 ? "s" : "") + " "
				"Machine is " + state;

			return fmt;
		}

	private:
		void Dispense()
		{
			switch (m_state)
			{
			case State::Sold:
				--m_count;
				--m_quartersCount;
				std::cout << "A gumball comes rolling out the slot...\n";
				if (m_count == 0)
				{
					m_state = State::SoldOut;
					return;
				}
				if (m_quartersCount == 0)
				{
					m_state = State::NoQuarter;
					return;
				}
				m_state = State::HasQuarters;
				break;
			case State::NoQuarter:
				std::cout << "You need to pay first\n";
				break;
			case State::SoldOut:
			case State::HasQuarters:
				std::cout << "No gumball dispensed\n";
				break;
			}
		}

		unsigned m_count;	// Количество шариков
		unsigned m_quartersCount = 0;
		State m_state = State::SoldOut;
	};
}