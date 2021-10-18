#include "CConstDocumentItem.h"

using namespace std;

CConstDocumentItem::CConstDocumentItem(std::shared_ptr<IImage> image, std::shared_ptr<IParagraph> paragraph)
	: m_image(image)
	, m_paragraph(paragraph)
{}
std::shared_ptr<const IImage> CConstDocumentItem::GetImage()const
{
	return m_image;
}
std::shared_ptr<const IParagraph> CConstDocumentItem::GetParagraph()const
{
	return m_paragraph;
}