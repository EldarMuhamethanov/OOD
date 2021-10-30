#pragma once
#include "CAbstractCommand.h"
#include "IDocument.h"
#include <functional>

class CInsertParagraph : public CAbstractCommand
{
public:
	CInsertParagraph(std::function<void()> onInsert, std::function<void()> onDelete);

	void DoExecute();
	void DoUnexecute();
private:
	std::function<void()> m_execute;
	std::function<void()> m_unexecute;
};

