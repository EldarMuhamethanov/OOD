#pragma once
#include "CConstDocumentItem.h"

class CDocumentItem: public CConstDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<IImage> image, std::shared_ptr<IParagraph> paragraph);
	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<IImage> GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<IParagraph> GetParagraph();
};
