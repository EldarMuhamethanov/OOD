#include "CReplaceText.h"
#include <string>
#include <stdexcept>

using namespace std;

CReplaceText::CReplaceText(IDocument& document, size_t position, std::string const& newText)
	: m_document(document)
	, m_position(position)
	, m_newText(newText)
{
	CDocumentItem item = document.GetItem(position);
	shared_ptr<IParagraph> paragraph = item.GetParagraph();
	m_oldText = paragraph->GetText();
}

void CReplaceText::DoExecute()
{
	m_document.ReplaceText(m_position, m_newText);
}
void CReplaceText::DoUnexecute()
{
	m_document.ReplaceText(m_position, m_oldText);
}