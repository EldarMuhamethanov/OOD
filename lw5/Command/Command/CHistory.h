#pragma once
#include <deque>
#include "IHistory.h"

const short int MAX_HISTORY_SIZE = 10;

class CHistory: public IHistory
{
public:
	CHistory();

	bool CanUndo()const;
	void Undo();
	bool CanRedo()const;
	void Redo();
	void AddAndExecuteCommand(ICommandPtr&& command);
private:
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};
