#pragma once
#include <memory>
#include <string>
#include "IParagraph.h"
#include "IImage.h"
#include "CConstDocumentItem.h"
#include "CDocumentItem.h"
#include "IImageStorage.h"
#include "ICommand_fwd.h"

class IDocument
{
public:
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	virtual std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, const size_t position) = 0;

	virtual void ReplaceText(size_t position, const std::string& newText) = 0;

	//// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	//// �������� path ������ ���� � ������������ �����������
	//// ��� ������� ����������� ������ ������������ � ���������� images 
	//// ��� ������������� ��������������� ������
	virtual std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height, const size_t position) = 0;

	virtual void ResizeImage(size_t position, int newWidth, int newHeight) = 0;

	virtual void AddItem(CDocumentItem& item, size_t position) = 0;

	//// ���������� ���������� ��������� � ���������
	virtual size_t GetItemsCount()const = 0;

	//// ������ � ��������� �����������
	virtual CConstDocumentItem GetItem(size_t index)const = 0;
	virtual CDocumentItem GetItem(size_t index) = 0;

	//// ������� ������� �� ���������
	virtual void DeleteItem(size_t index) = 0;

	// ���������� ��������� ���������
	virtual std::string GetTitle()const = 0;
	// �������� ��������� ���������
	virtual void SetTitle(const std::string& title) = 0;

	// �������� � ����������� �������� Undo
	virtual bool CanUndo()const = 0;
	// �������� ������� ��������������
	virtual void Undo() = 0;

	// �������� � ����������� �������� Redo
	virtual bool CanRedo()const = 0;
	// ��������� ���������� ������� ��������������
	virtual void Redo() = 0;

	//// ��������� �������� � ������� html. ����������� ����������� � ���������� images.
	//// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	virtual void Save(const std::string& path)const = 0;

	virtual void PrintContent(std::ostream& out)const = 0;

	virtual void ApplyCommand(ICommandPtr&& command) = 0;

	virtual IImagesStorage& GetImageStorage() = 0;

	virtual ~IDocument() = default;
};
