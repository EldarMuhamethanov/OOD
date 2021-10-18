#include "CDocumentItem.h"
#include <memory>

using namespace std;

CDocumentItem::CDocumentItem(shared_ptr<IImage> image, shared_ptr<IParagraph> paragraph)
	: CConstDocumentItem(image, paragraph)
{}
std::shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}
std::shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}