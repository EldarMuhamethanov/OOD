#pragma once
#include "GumballMachineWithState.h"
#include "CMenu.h"

class CGumballMachineController
{
public:
	CGumballMachineController(unsigned ballsCount = 0);
	void Start();
private:
	typedef void (CGumballMachineController::* MenuHandler)(std::istream&);

	void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler);
	void EjectQuarters(std::istream& in);
	void InsertQuarter(std::istream& in);
	void TurnCrank(std::istream& in);
	void Refill(std::istream& in);
	void Info(std::istream& in);

	CMenu m_menu;
	std::unique_ptr<with_state::CGumballMachine> m_gumbleMachine;
};

