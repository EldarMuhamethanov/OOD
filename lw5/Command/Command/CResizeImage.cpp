#include "CResizeImage.h"

using namespace std;

CResizeImage::CResizeImage(IDocument& document, int position, int newWidth, int newHeight)
	: m_document(document)
	, m_position(position)
	, m_newWidth(newWidth)
	, m_newHeight(newHeight)
{
	CDocumentItem item = document.GetItem(position);
	shared_ptr<IImage> image = item.GetImage();
	m_oldWidth = image->GetWidth();
	m_oldHeight = image->GetHeight();
}

void CResizeImage::DoExecute()
{
	m_document.ResizeImage(m_position, m_newWidth, m_newHeight);
}

void CResizeImage::DoUnexecute()
{
	m_document.ResizeImage(m_position, m_oldWidth, m_oldHeight);
}