#include "CSetTitleCommand.h"

CSetTitleCommand::CSetTitleCommand(IDocument& document, const std::string newTitle)
	: m_document(document)
	, m_newTitle(newTitle)
	, m_oldTitle(document.GetTitle())
{}

void CSetTitleCommand::DoExecute()
{
	m_document.SetTitle(m_newTitle);
}
void CSetTitleCommand::DoUnexecute()
{
	m_document.SetTitle(m_oldTitle);
}