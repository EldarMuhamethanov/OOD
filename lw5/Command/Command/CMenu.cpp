#include "CMenu.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

CMenu::CMenu(istream& input, ostream& output)
	: m_input(input)
	, m_output(output)
{}

void CMenu::AddItem(string const& shortcut, string const& description, const Command& command)
{
	m_items.emplace_back(shortcut, description, command);
}

void CMenu::Run()
{
	ShowInstructions();

	string command;
	while ((m_output << ">")
		&& getline(m_input, command)
		&& ExecuteCommand(command))
	{
	}
}

void CMenu::ShowInstructions() const
{
	m_output << "Commands list:\n";
	for (auto& item : m_items)
	{
		m_output << "  " << item.shortcut << ": " << item.description << "\n";
	}
}

void CMenu::Exit()
{
	m_exit = true;
}

bool CMenu::ExecuteCommand(const string& command)
{
	istringstream iss(command);
	string name;
	iss >> name;

	m_exit = false;
	auto it = find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
		return item.shortcut == name;
		});
	if (it != m_items.end())
	{
		try
		{
			it->command(iss);
		}
		catch (exception const& e)
		{
			m_output << e.what() << endl;
		}
	}
	else
	{
		m_output << "Unknown command\n";
	}
	return !m_exit;
}
