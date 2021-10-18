#pragma once
#include <vector>
#include "IDocument.h"
#include "CHistory.h"
#include "CImagesStorage.h"
#include "ICommand.h"

class CDocument :public IDocument
{
public:
	CDocument();
	void SetTitle(const std::string& title) override;
	std::string GetTitle() const override;

	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text, const size_t position) override;
	void ReplaceText(size_t position, const std::string& newText) override;

	std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height, const size_t position) override;
	void ResizeImage(size_t position, int newWidth, int newHeight) override;

	void AddItem(CDocumentItem& item, size_t position) override;
	size_t GetItemsCount()const override;
	CConstDocumentItem GetItem(size_t index)const override;
	CDocumentItem GetItem(size_t index) override;

	void DeleteItem(size_t index) override;

	void PrintContent(std::ostream& out)const override;
	void Save(const std::string& path)const override;

	bool CanUndo() const override;
	void Undo() override;
	bool CanRedo() const override;
	void Redo() override;

	void ApplyCommand(ICommandPtr&& command) override;
	IImagesStorage& GetImageStorage() override;

private:
	std::string m_title;
	std::vector<CDocumentItem> m_items;
	CImagesStorage m_imageStorage;
	CHistory m_history;
};