#pragma once
#include <iostream>
#include <string>

namespace with_state
{
	const unsigned MAX_QUARTERS_COUNT = 5;

	struct IState
	{
		virtual void InsertQuarter() = 0;
		virtual void EjectQuarters() = 0;
		virtual void TurnCrank() = 0;
		virtual void Dispense() = 0;
		virtual void Refill(unsigned count) = 0;
		virtual std::string ToString()const = 0;
		virtual ~IState() = default;
	};

	struct IGumballMachineWithState
	{
		virtual void ReleaseBall() = 0;
		virtual void UseQuarter() = 0;
		virtual void RemoveAllQuarters() = 0;
		virtual void AddQuarter() = 0;
		virtual void AddGumBalls(unsigned count) = 0;
		virtual unsigned GetQuartersCount() const = 0;
		virtual unsigned GetBallCount()const = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;

		virtual ~IGumballMachineWithState() = default;
	};

	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachineWithState& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}
		void InsertQuarter() override
		{
			std::cout << "Please wait, we're already giving you a gumball\n";
		}
		void EjectQuarters() override
		{
			std::cout << "Sorry you already turned the crank\n";
		}
		void TurnCrank() override
		{
			std::cout << "Turning twice doesn't get you another gumball\n";
		}
		void Dispense() override
		{
			m_gumballMachine.ReleaseBall();
			m_gumballMachine.UseQuarter();
			if (m_gumballMachine.GetBallCount() == 0)
			{
				m_gumballMachine.SetSoldOutState();
				return;
			}
			if (m_gumballMachine.GetQuartersCount() == 0) 
			{
				m_gumballMachine.SetNoQuarterState();
				return;
			}
			m_gumballMachine.SetHasQuarterState();
		}
		void Refill(unsigned count) override
		{
			std::cout << "Can't refill gumballs, while sold gumball";
		}
		std::string ToString() const override
		{
			return "delivering a gumball";
		}
	private:
		IGumballMachineWithState& m_gumballMachine;
	};

	class CSoldOutState : public IState
	{
	public:
		CSoldOutState(IGumballMachineWithState& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You can't insert a quarter, the machine is sold out\n";
		}
		void EjectQuarters() override
		{
			std::cout << "Return quarters\n";
			m_gumballMachine.RemoveAllQuarters();
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no gumballs\n";
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		void Refill(unsigned count) override
		{
			if (count == 0)
				return;

			m_gumballMachine.AddGumBalls(count);
			unsigned quartersCount = m_gumballMachine.GetQuartersCount();
			if (quartersCount > 0)
			{
				m_gumballMachine.SetHasQuarterState();
				return;
			}
			m_gumballMachine.SetNoQuarterState();
		}
		std::string ToString() const override
		{
			return "sold out";
		}
	private:
		IGumballMachineWithState& m_gumballMachine;
	};

	class CHasQuarterState : public IState
	{
	public:
		CHasQuarterState(IGumballMachineWithState& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			if (m_gumballMachine.GetQuartersCount() == MAX_QUARTERS_COUNT)
			{
				std::cout << "Cant Insert quarters, Amount of quarters is max\n";
				return;
			}
			std::cout << "Insert one more Quarter\n";
			m_gumballMachine.AddQuarter();
		}
		void EjectQuarters() override
		{
			std::cout << "Quarters returned\n";
			m_gumballMachine.RemoveAllQuarters();
			m_gumballMachine.SetNoQuarterState();
		}
		void TurnCrank() override
		{
			std::cout << "You turned...\n";
			m_gumballMachine.SetSoldState();
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		void Refill(unsigned count) override
		{
			m_gumballMachine.AddGumBalls(count);
		}
		std::string ToString() const override
		{
			return "waiting for turn of crank";
		}
	private:
		IGumballMachineWithState& m_gumballMachine;
	};

	class CNoQuarterState : public IState
	{
	public:
		CNoQuarterState(IGumballMachineWithState& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You inserted a quarter\n";
			m_gumballMachine.AddQuarter();
			m_gumballMachine.SetHasQuarterState();
		}
		void EjectQuarters() override
		{
			std::cout << "You haven't inserted a quarter\n";
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no quarter\n";
		}
		void Dispense() override
		{
			std::cout << "You need to pay first\n";
		}
		void Refill(unsigned count) override
		{
			m_gumballMachine.AddGumBalls(count);
		}
		std::string ToString() const override
		{
			return "waiting for quarter";
		}
	private:
		IGumballMachineWithState& m_gumballMachine;
	};

	class CGumballMachine : private IGumballMachineWithState
	{
	public:
		CGumballMachine(unsigned numBalls)
			: m_soldState(*this)
			, m_soldOutState(*this)
			, m_noQuarterState(*this)
			, m_hasQuarterState(*this)
			, m_state(&m_soldOutState)
			, m_count(numBalls)
		{
			if (m_count > 0)
			{
				m_state = &m_noQuarterState;
			}
		}
		void EjectQuarters()
		{
			m_state->EjectQuarters();
		}
		void InsertQuarter()
		{
			m_state->InsertQuarter();
		}
		void TurnCrank()
		{
			m_state->TurnCrank();
			m_state->Dispense();
		}
		void Refill(unsigned numBalls)
		{
			m_state->Refill(numBalls);
		}
		std::string ToString()const
		{
			std::string fmt = "Mighty Gumball, Inc."
				"C++ - enabled Standing Gumball Model #2016 (with state)"
				"Inventory: " + std::to_string(m_count) + " gumball " + (m_count != 1 ? "s" : "") + " "
				"Quarters: " + std::to_string(m_quartersCount) + " quarters " + (m_quartersCount != 1 ? "s" : "") + " "
				"Machine is " + m_state->ToString();

			return fmt;
		}
	private:
		unsigned GetBallCount() const override
		{
			return m_count;
		}
		unsigned GetQuartersCount() const override
		{
			return m_quartersCount;
		}
		void AddQuarter() override
		{
			if (m_quartersCount == MAX_QUARTERS_COUNT) {
				std::cout << "max amount of quarters";
				return;
			}
			++m_quartersCount;
		}
		void RemoveAllQuarters() override
		{
			m_quartersCount = 0;
		}
		void UseQuarter() override
		{
			if (m_quartersCount == 0) {
				std::cout << "out of quarters";
				return;
			}
			--m_quartersCount;
		}
		void ReleaseBall() override
		{
			if (m_count != 0)
			{
				std::cout << "A gumball comes rolling out the slot...\n";
				--m_count;
			}
		}
		void AddGumBalls(unsigned count) override
		{
			std::cout << "Add Gum balls in gumballMachine\n";
			m_count += count;
		}
		void SetSoldOutState() override
		{
			m_state = &m_soldOutState;
		}
		void SetNoQuarterState() override
		{
			m_state = &m_noQuarterState;
		}
		void SetSoldState() override
		{
			m_state = &m_soldState;
		}
		void SetHasQuarterState() override
		{
			m_state = &m_hasQuarterState;
		}
	private:
		unsigned m_count = 0;
		unsigned m_quartersCount = 0;
		CSoldState m_soldState;
		CSoldOutState m_soldOutState;
		CNoQuarterState m_noQuarterState;
		CHasQuarterState m_hasQuarterState;
		IState* m_state;
	};

}
