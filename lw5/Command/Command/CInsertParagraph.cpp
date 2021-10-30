#include "CInsertParagraph.h"

CInsertParagraph::CInsertParagraph(std::function<void()> onInsert, std::function<void()> onDelete)
	: m_execute(onInsert)
	, m_unexecute(onDelete)
{}

void CInsertParagraph::DoExecute()
{
	m_execute();
}

void CInsertParagraph::DoUnexecute()
{
	m_unexecute();
}