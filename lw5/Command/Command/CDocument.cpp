#include "CDocument.h"
#include "CChangeStringCommand.h"
#include "CInsertParagraph.h"
#include "CSetTitleCommand.h"
#include "CParagraph.h"
#include "CImage.h"
#include "CHtmlConverter.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;
namespace fs = std::filesystem;

const string IMAGE_STORAGE_FOLDER = "images";

CDocument::CDocument()
	: m_imageStorage(IMAGE_STORAGE_FOLDER)
{}

void CDocument::SetTitle(const std::string& title)
{
	string oldTitle = GetTitle();
	unique_ptr<ICommand> command = make_unique<CSetTitleCommand>(
		[&, title]() {
			m_title = title;
		},
		[&, oldTitle]() {
			m_title = oldTitle;
		}
		);
	ApplyCommand(move(command));
	m_title = title;
}
std::string CDocument::GetTitle() const
{
	return m_title;
}
shared_ptr<IParagraph> CDocument::InsertParagraph(const string& text, const size_t position)
{
	shared_ptr<IParagraph> paragraph = make_shared<CParagraph>(text);
	unique_ptr<ICommand> command = make_unique<CInsertParagraph>(
		[&, position]() {
			CDocumentItem item(nullptr, paragraph);
			AddItem(item, position);
		},
		[&, position]() {
			DeleteItem(position);
		}
	);
	ApplyCommand(move(command));
	return paragraph;
}
void CDocument::ReplaceText(size_t position, const string& newText)
{
	if (position < GetItemsCount())
	{
		CDocumentItem item = GetItem(position);
		shared_ptr<IParagraph> paragraph = item.GetParagraph();
		if (paragraph != nullptr) {
			paragraph->SetText(newText);
			return;
		}
		string error = "Item in position " + to_string(position) + " isnt paragraph";
		throw exception(error.c_str());
	}
	throw exception("index is out of range");
}
shared_ptr<IImage> CDocument::InsertImage(const string& path, int width, int height, const size_t position)
{
	if (width > 10000 || height > 10000 || width <= 0 || height <= 0)
	{
		throw invalid_argument("image height and width must be <= 10000 and > 0");
	}
	string newPath = m_imageStorage.AddFile(path);
	shared_ptr<IImage> image = make_shared<CImage>(newPath, width, height);
	CDocumentItem item(image, nullptr);
	AddItem(item, position);
	return image;
}
void CDocument::ResizeImage(size_t position, int newWidth, int newHeight)
{
	if (position < GetItemsCount())
	{
		CDocumentItem item = GetItem(position);
		shared_ptr<IImage> image = item.GetImage();
		if (image != nullptr) {
			image->Resize(newWidth, newHeight);
			return;
		}
		string error = "Item in position " + to_string(position) + " isnt image";
		throw exception(error.c_str());
	}
	throw exception("index is out of range");
}
void CDocument::AddItem(CDocumentItem& item, size_t position)
{
	if (position <= GetItemsCount())
	{
		m_items.insert(m_items.begin() + position, item);
		return;
	}
	throw exception("index is out of range");
}
size_t CDocument::GetItemsCount()const
{
	return m_items.size();
}
CConstDocumentItem CDocument::GetItem(size_t index)const
{
	if (index < GetItemsCount())
	{
		CConstDocumentItem item = m_items[index];
		return item;
	}
	throw exception("index is out of range");
}
CDocumentItem CDocument::GetItem(size_t index)
{
	if (index < GetItemsCount())
	{
		return m_items[index];
	}
	throw exception("index is out of range");
}
void CDocument::DeleteItem(size_t index)
{
	if (index < GetItemsCount())
	{
		m_items.erase(m_items.begin() + index);
		return;
	}
	throw exception("index is out of range");
}
void CDocument::Save(const std::string& path)const
{
	ofstream out(path);
	fs::path fsPath = path;
	auto resultPath = fsPath.parent_path() / IMAGE_STORAGE_FOLDER;
	filesystem::copy(IMAGE_STORAGE_FOLDER, resultPath.u8string(), filesystem::copy_options::recursive | filesystem::copy_options::overwrite_existing);
	// принимать интерфейс print
	CHtmlConverter::PrintDocument(*this, out);
}

void CDocument::PrintContent(std::ostream& out)const
{
	out << "Title: " << GetTitle() << endl;
	for (size_t i = 0; i < GetItemsCount(); i++)
	{
		out << i << ". ";
		CConstDocumentItem item = GetItem(i);
		shared_ptr<const IParagraph> paragraph = item.GetParagraph();
		if (paragraph != nullptr)
		{
			out << "Paragraph: " << paragraph->GetText() << endl;
			continue;
		}
		shared_ptr<const IImage> image = item.GetImage();
		if (image != nullptr)
		{
			out << "Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << endl;
		}
	}
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}
void CDocument::Undo()
{
	m_history.Undo();
}
bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}
void CDocument::Redo()
{
	m_history.Redo();
}

void CDocument::ApplyCommand(ICommandPtr&& command)
{
	return m_history.AddAndExecuteCommand(move(command));
}

IImagesStorage& CDocument::GetImageStorage()
{
	return m_imageStorage;
}