#pragma once
#include "CConstDocumentItem.h"

class CDocumentItem: public CConstDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<IImage> image, std::shared_ptr<IParagraph> paragraph);
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph();
};
