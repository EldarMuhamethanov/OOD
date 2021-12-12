#include "CGumballMachineController.h"
#include "GumballMachineWithState.h"

using namespace std;
using namespace std::placeholders;

CGumballMachineController::CGumballMachineController(unsigned ballsCount)
	: m_gumbleMachine(make_unique<with_state::CGumballMachine>(ballsCount))
	, m_menu(cin, cout)
{
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	AddMenuItem("insertQuarter", "Insert quarter", &CGumballMachineController::InsertQuarter);
	AddMenuItem("turnCrank", "Turn Crank", &CGumballMachineController::TurnCrank);
	AddMenuItem("ejectQuarters", "Eject quarters", &CGumballMachineController::EjectQuarters);
	AddMenuItem("refill", "Refill machine: Args: <count>", &CGumballMachineController::Refill);
	AddMenuItem("info", "Get info", &CGumballMachineController::Info);
}

void CGumballMachineController::Start()
{
	m_menu.Run();
}

void CGumballMachineController::AddMenuItem(const string& shortcut, const string& description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, _1));
}

void CGumballMachineController::EjectQuarters(istream&)
{
	m_gumbleMachine->EjectQuarters();
}
void CGumballMachineController::InsertQuarter(istream&)
{
	m_gumbleMachine->InsertQuarter();
}
void CGumballMachineController::TurnCrank(istream&)
{
	m_gumbleMachine->TurnCrank();
}
void CGumballMachineController::Refill(istream& in)
{
	unsigned count;
	in >> count;
	m_gumbleMachine->Refill(count);
}
void CGumballMachineController::Info(istream&)
{
	cout << m_gumbleMachine->ToString() << endl;
}