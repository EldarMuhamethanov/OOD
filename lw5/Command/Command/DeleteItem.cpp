#include "DeleteItem.h"

using namespace std;

CDeleteItem::CDeleteItem(IDocument& document, size_t position)
	: m_document(document)
	, m_position(position)
{
	CDocumentItem item = document.GetItem(position);
	m_oldItem = new CDocumentItem(item.GetImage(), item.GetParagraph());
}

void CDeleteItem::DoExecute()
{
	m_document.DeleteItem(m_position);
}

void CDeleteItem::DoUnexecute()
{
	m_document.AddItem(*m_oldItem, m_position);
}