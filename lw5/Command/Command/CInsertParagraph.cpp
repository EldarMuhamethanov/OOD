#include "CInsertParagraph.h"

CInsertParagraph::CInsertParagraph(IDocument& document, std::string const& text, int position)
	: m_document(document)
	, m_text(text)
	, m_position(position)
{}

void CInsertParagraph::DoExecute()
{
	m_document.InsertParagraph(m_text, m_position);
}

void CInsertParagraph::DoUnexecute()
{
	m_document.DeleteItem(m_position);
}