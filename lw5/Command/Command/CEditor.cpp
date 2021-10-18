#include "CEditor.h"
#include "CSetTitleCommand.h"
#include "CInsertParagraph.h"
#include "CReplaceText.h"
#include "CInsertImage.h"
#include "CResizeImage.h"
#include "DeleteItem.h"
#include "CHtmlConverter.h"
#include <iostream>

using namespace std;
using namespace std::placeholders;


CEditor::CEditor(istream& in, ostream& out)
	: m_document(make_unique<CDocument>())
	, m_menu(in, out)
	, m_input(in)
	, m_output(out)
{
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	m_menu.AddItem("list", "Show document", bind(&CEditor::List, this, _1));
	AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
	AddMenuItem("insertParagraph", "Insert Paragraph. Args: <position>|end <text>" , &CEditor::InsertParagraph);
	AddMenuItem("replaceText", "Replace paragraph text. Args: <position> <text>" , &CEditor::ReplaceText);
	AddMenuItem("insertImage", "Insert image. Args: <position>|end <width> <height> <path>" , &CEditor::InsertImage);
	AddMenuItem("resizeImage", "Resize Image. Args: <position> <width> <height>" , &CEditor::ResizeImage);
	AddMenuItem("delete", "Delete element. Args: <position>" , &CEditor::DeleteItem);
	AddMenuItem("save", "Save document. Args: <path>" , &CEditor::SaveDocument);
	AddMenuItem("undo", "Undo command", &CEditor::Undo);
	AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const string& shortcut, const string& description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, _1));
}

void CEditor::SetTitle(istream& in)
{
	string head;
	string tail;

	if (in >> head)
	{
		getline(in, tail);
	}
	string title = head + tail;

	unique_ptr<ICommand> setTitleCommand = make_unique<CSetTitleCommand>(*m_document, title);
	m_document->ApplyCommand(move(setTitleCommand));
}

void CEditor::InsertParagraph(istream& in)
{
	string userPosition;
	string userText;
	in >> userPosition;
	getline(in, userText);
	size_t position;
	try
	{
		position = userPosition == "end"
			? m_document->GetItemsCount()
			: stoi(userPosition);
	}
	catch (...)
	{
		throw exception("invalid position");
	}
	unique_ptr<ICommand> insertParagraphCommand = make_unique<CInsertParagraph>(*m_document, userText, position);
	m_document->ApplyCommand(move(insertParagraphCommand));
}

void CEditor::ReplaceText(istream& in)
{
	size_t position;
	string userText;
	in >> position;
	getline(in, userText);
	unique_ptr<ICommand> replaceTextCommand = make_unique<CReplaceText>(*m_document, position, userText);
	m_document->ApplyCommand(move(replaceTextCommand));
}

void CEditor::InsertImage(istream& in)
{
	string path;
	size_t width;
	size_t height;
	string userPosition;
	in >> userPosition >> width >> height >> path;
	size_t position;
	try
	{
		position = userPosition == "end"
			? m_document->GetItemsCount()
			: stoi(userPosition);
	}
	catch (...)
	{
		throw exception("invalid position");
	}
	unique_ptr<ICommand> insertImageCommand = make_unique<CInsertImage>(*m_document, path, width, height, position);
	m_document->ApplyCommand(move(insertImageCommand));
}

void CEditor::ResizeImage(istream& in)
{
	size_t position;
	size_t width;
	size_t height;
	in >> position >> width >> height;
	unique_ptr<ICommand> resizeImageCommand = make_unique<CResizeImage>(*m_document, position, width, height);
	m_document->ApplyCommand(move(resizeImageCommand));
}

void CEditor::DeleteItem(std::istream& in)
{
	size_t position;
	in >> position;
	unique_ptr<ICommand> deleteCommand = make_unique<CDeleteItem>(*m_document, position);
	m_document->ApplyCommand(move(deleteCommand));
}

void CEditor::SaveDocument(std::istream& in)
{
	string path;
	in >> path;
	m_document->Save(path);
}

void CEditor::List(istream&)
{
	m_output << "-------------" << endl;
	m_document->PrintContent(m_output);
	m_output << "-------------" << endl;
}

void CEditor::Undo(istream&)
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		m_output << "Can't undo" << endl;
	}
}

void CEditor::Redo(istream&)
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		m_output << "Can't redo" << endl;
	}
}