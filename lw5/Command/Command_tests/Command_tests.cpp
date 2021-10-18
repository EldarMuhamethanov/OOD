#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Command/CParagraph.h"
#include "../Command/CImage.h"
#include "../Command/CDocumentItem.h"
#include "../Command/CDocument.h"
#include "../Command/DeleteItem.h"
#include "../Command/CInsertImage.h"
#include "../Command/CInsertParagraph.h"
#include "../Command/CReplaceText.h"
#include "../Command/CResizeImage.h"
#include "../Command/CSetTitleCommand.h"
#include "../Command/ICommand_fwd.h"
#include "../Command/ICommand.h"
#include "../Command/CHtmlConverter.h"
#include "../Command/CMenu.h"
#include "../Command/CEditor.h"
#include "CMockCommand.h"
#include <iostream>
#include <sstream>
#include <memory>

using namespace std;

void CheckIsValidParagraph(IDocument& document, int position, string const& text)
{
	CDocumentItem item = document.GetItem(position);
	shared_ptr<IParagraph> paragraph = item.GetParagraph();
	REQUIRE(paragraph != nullptr);
	REQUIRE(paragraph->GetText() == text);
}

void CheckIsValidImage(IDocument& document, int position, string const& path, int width, int heigth)
{
	CDocumentItem item = document.GetItem(position);
	shared_ptr<IImage> image = item.GetImage();
	REQUIRE(image != nullptr);
	REQUIRE(image->GetPath() == path);
	REQUIRE(image->GetHeight() == heigth);
	REQUIRE(image->GetWidth() == width);
}

SCENARIO("tests paragraph")
{
	CParagraph paragraph("text");
	REQUIRE(paragraph.GetText() == "text");

	paragraph.SetText("new text");
	REQUIRE(paragraph.GetText() == "new text");
}

SCENARIO("tests image")
{
	CImage image("image.jpg", 100, 200);
	REQUIRE(image.GetHeight() == 200);
	REQUIRE(image.GetWidth() == 100);
	REQUIRE(image.GetPath() == "image.jpg");

	image.Resize(150, 350);
	REQUIRE(image.GetHeight() == 350);
	REQUIRE(image.GetWidth() == 150);
}

SCENARIO("tests document item")
{
	shared_ptr<IParagraph> paragraph = make_shared<CParagraph>("text");
	shared_ptr<IImage> image = make_shared<CImage>("file.jpg", 100, 100);
	CDocumentItem item1(nullptr, paragraph);
	CDocumentItem item2(image, nullptr);

	REQUIRE(item1.GetParagraph() == paragraph);
	REQUIRE(item2.GetImage() == image);
}

SCENARIO("tests Document")
{
	CDocument document;
	REQUIRE(document.GetTitle() == "");
	REQUIRE(document.GetItemsCount() == 0);

	WHEN("set title")
	{
		document.SetTitle("title");
		REQUIRE(document.GetTitle() == "title");
	}
	WHEN("insert paragraph")
	{
		document.InsertParagraph("text", 0);
		REQUIRE(document.GetItemsCount() == 1);
		CDocumentItem item = document.GetItem(0);
		shared_ptr<IParagraph> paragraph = item.GetParagraph();
		shared_ptr<IImage> image = item.GetImage();
		REQUIRE(image == nullptr);
		REQUIRE(paragraph->GetText() == "text");
		
		REQUIRE_THROWS(document.InsertParagraph("invalid", 2));
		REQUIRE_THROWS(document.GetItem(1));
		WHEN("replace text")
		{
			document.ReplaceText(0, "new text");
			REQUIRE(paragraph->GetText() == "new text");
			REQUIRE_THROWS(document.ReplaceText(1, "new text"));
		}
	}
	WHEN("insert Image")
	{
		document.InsertImage("image.jpg", 100, 200, 0);
		REQUIRE(document.GetItemsCount() == 1);
		CDocumentItem item = document.GetItem(0);
		shared_ptr<IParagraph> paragraph = item.GetParagraph();
		shared_ptr<IImage> image = item.GetImage();
		REQUIRE(image->GetHeight() == 200);
		REQUIRE(image->GetWidth() == 100);
		REQUIRE(image->GetPath() == "images\\image(0).jpg");
		REQUIRE(paragraph == nullptr);

		WHEN("resize image")
		{
			document.ResizeImage(0, 150, 350);
			REQUIRE(image->GetHeight() == 350);
			REQUIRE(image->GetWidth() == 150);
			REQUIRE_THROWS(document.ResizeImage(1, 150, 350));
		}
	}
	WHEN("Delete item")
	{
		document.InsertParagraph("text", 0);
		REQUIRE_THROWS(document.DeleteItem(1));
		document.DeleteItem(0);
		REQUIRE(document.GetItemsCount() == 0);
	}
	WHEN("Print data")
	{
		document.SetTitle("title");
		document.InsertParagraph("text", 0);
		document.InsertImage("image.jpg", 100, 200, 1);

		string result = "Title: title\n"
			"0. Paragraph: text\n"
			"1. Image: 100 200 images\\image(0).jpg\n";

		string resultStream;
		ostringstream strm(resultStream);

		document.PrintContent(strm);
		REQUIRE(strm.str() == result);
	}
	WHEN("apply/undo/redo")
	{
		unique_ptr<ICommand> setTitleCommand = make_unique<CSetTitleCommand>(document, "title");
		document.ApplyCommand(move(setTitleCommand));
		REQUIRE(document.GetTitle() == "title");
		REQUIRE(document.CanUndo());
		REQUIRE(!document.CanRedo());
		
		document.Undo();
		REQUIRE(document.GetTitle() == "");
		REQUIRE(!document.CanUndo());
		REQUIRE(document.CanRedo());
		
		document.Redo();
		REQUIRE(document.GetTitle() == "title");
		REQUIRE(document.CanUndo());
		REQUIRE(!document.CanRedo());
	}
}

SCENARIO("test commands")
{
	CDocument document;

	WHEN("set title")
	{
		unique_ptr<ICommand> setTitleCommand = make_unique<CSetTitleCommand>(document, "title");
		setTitleCommand->Execute();
		REQUIRE(document.GetTitle() == "title");
		setTitleCommand->Unexecute();
		REQUIRE(document.GetTitle() == "");
	}
	
	WHEN("insert paragraph")
	{
		unique_ptr<ICommand> insertParagraphCommand = make_unique<CInsertParagraph>(document, "text 1", 0);
		insertParagraphCommand->Execute();
		REQUIRE(document.GetItemsCount() == 1);
		CheckIsValidParagraph(document, 0, "text 1");
		insertParagraphCommand->Unexecute();
		REQUIRE(document.GetItemsCount() == 0);
	}
	
	WHEN("insertImage")
	{
		unique_ptr<ICommand> insertImageCommand = make_unique<CInsertImage>(document, "image.jpg", 100, 200, 0);
		insertImageCommand->Execute();
		REQUIRE(document.GetItemsCount() == 1);
		CheckIsValidImage(document, 0, "images\\image(0).jpg", 100, 200);
		insertImageCommand->Unexecute();
		REQUIRE(document.GetItemsCount() == 0);
	}
	
	WHEN("replace text")
	{
		document.InsertParagraph("text", 0);
		unique_ptr<ICommand> replaceTextCommand = make_unique<CReplaceText>(document, 0, "new Text");
		replaceTextCommand->Execute();
		CheckIsValidParagraph(document, 0, "new Text");
		replaceTextCommand->Unexecute();
		CheckIsValidParagraph(document, 0, "text");
	}

	WHEN("resize image")
	{
		document.InsertImage("image.jpg", 100, 200, 0);
		unique_ptr<ICommand> resizeImage = make_unique<CResizeImage>(document, 0, 150, 300);
		resizeImage->Execute();
		CheckIsValidImage(document, 0, "images\\image(0).jpg", 150, 300);
		resizeImage->Unexecute();
		CheckIsValidImage(document, 0, "images\\image(0).jpg", 100, 200);
	}

	WHEN("delete item")
	{
		document.InsertParagraph("text", 0);
		document.InsertImage("image.jpg", 100, 200, 1);
		REQUIRE(document.GetItemsCount() == 2);
		unique_ptr<ICommand> deleteItem = make_unique<CDeleteItem>(document, 0);
		deleteItem->Execute();
		REQUIRE(document.GetItemsCount() == 1);
		CheckIsValidImage(document, 0, "images\\image(0).jpg", 100, 200);
		deleteItem->Unexecute();
		REQUIRE(document.GetItemsCount() == 2);
		CheckIsValidParagraph(document, 0, "text");
		CheckIsValidImage(document, 1, "images\\image(0).jpg", 100, 200);
	}
}

SCENARIO("test history")
{
	CHistory history;

	WHEN("add commands and undo/redo")
	{
		unique_ptr<ICommand> mockCommand1 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand2 = make_unique<CMockCommand>();
		history.AddAndExecuteCommand(move(mockCommand1));
		history.AddAndExecuteCommand(move(mockCommand2));

		REQUIRE(history.CanUndo());
		REQUIRE(!history.CanRedo());

		WHEN("first undo")
		{
			history.Undo();
			REQUIRE(history.CanUndo());
			REQUIRE(history.CanRedo());

			WHEN("last undo")
			{
				history.Undo();
				REQUIRE(!history.CanUndo());
				REQUIRE(history.CanRedo());

				WHEN("first redo")
				{
					history.Redo();
					REQUIRE(history.CanUndo());
					REQUIRE(history.CanRedo());

					WHEN("last redo")
					{
						history.Redo();
						REQUIRE(history.CanUndo());
						REQUIRE(!history.CanRedo());
					}
				}
			}
		}
	}
	WHEN("do 2 command undo then do new command")
	{
		unique_ptr<ICommand> mockCommand1 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand2 = make_unique<CMockCommand>();

		history.AddAndExecuteCommand(move(mockCommand1));
		history.AddAndExecuteCommand(move(mockCommand2));

		WHEN("2 undo")
		{
			history.Undo();
			history.Undo();
			REQUIRE(!history.CanUndo());
			REQUIRE(history.CanRedo());
			WHEN("do new command")
			{
				unique_ptr<ICommand> mockCommand3 = make_unique<CMockCommand>();
				history.AddAndExecuteCommand(move(mockCommand3));
				REQUIRE(history.CanUndo());
				REQUIRE(!history.CanRedo());
				WHEN("undo again")
				{
					history.Undo();
					REQUIRE(!history.CanUndo());
					REQUIRE(history.CanRedo());
				}
			}
		}
	}

	WHEN("do 11 command then undo 10")
	{
		unique_ptr<ICommand> mockCommand1 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand2 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand3 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand4 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand5 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand6 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand7 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand8 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand9 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand10 = make_unique<CMockCommand>();
		unique_ptr<ICommand> mockCommand11 = make_unique<CMockCommand>();

		history.AddAndExecuteCommand(move(mockCommand1));
		history.AddAndExecuteCommand(move(mockCommand2));
		history.AddAndExecuteCommand(move(mockCommand3));
		history.AddAndExecuteCommand(move(mockCommand4));
		history.AddAndExecuteCommand(move(mockCommand5));
		history.AddAndExecuteCommand(move(mockCommand6));
		history.AddAndExecuteCommand(move(mockCommand7));
		history.AddAndExecuteCommand(move(mockCommand8));
		history.AddAndExecuteCommand(move(mockCommand9));
		history.AddAndExecuteCommand(move(mockCommand10));
		history.AddAndExecuteCommand(move(mockCommand11));

		history.Undo();
		history.Undo();
		history.Undo();
		history.Undo();
		history.Undo();
		history.Undo();
		history.Undo();
		history.Undo();
		history.Undo();
		history.Undo();

		REQUIRE(!history.CanUndo());
		REQUIRE(history.CanRedo());
	}
}

SCENARIO("test html html converter")
{
	CDocument document;
	document.SetTitle("title");
	document.InsertParagraph("text <div>1</div>", 0);
	document.InsertParagraph("'text' 2", 1);
	document.InsertImage("&image.jpg", 100, 200, 1);
	
	string result = "<html>\n"
		"<h1>title</h1>\n"
		"<p>text &lt;div&gt;1&lt;/div&gt;</p>\n"
		"<img src='images\\&amp;image(0).jpg' width='100' height='200' />\n"
		"<p>&apos;text&apos; 2</p>\n"
		"</html>\n";
	string out;
	ostringstream outStream(out);

	CHtmlConverter::PrintDocument(document, outStream);

	REQUIRE(outStream.str() == result);
}

SCENARIO("test menu")
{
	WHEN("Add items")
	{
		string input = "action2\naction1\naction3";
		istringstream inputStream(input);
		string output;
		ostringstream outputStream(output);

		CMenu menu(inputStream, outputStream);
		menu.AddItem("action1", "do action 1", [&outputStream](istream&) { outputStream << "do action 1" << endl; });
		menu.AddItem("action2", "do action 2", [&outputStream](istream&) {outputStream << "do action 2" << endl; });
		menu.AddItem("action3", "do action 3", [&outputStream](istream&) {outputStream << "do action 3" << endl; });

		WHEN("Show instructions")
		{
			string resultInstructions = "Commands list:\n"
				"  action1: do action 1\n"
				"  action2: do action 2\n"
				"  action3: do action 3\n";
			menu.ShowInstructions();
			REQUIRE(outputStream.str() == resultInstructions);
		}

		menu.Run();

		REQUIRE(outputStream.str() == "Commands list:\n"
			"  action1: do action 1\n"
			"  action2: do action 2\n"
			"  action3: do action 3\n"
			"Commands list:\n"
			"  action1: do action 1\n"
			"  action2: do action 2\n"
			"  action3: do action 3\n"
			">do action 2\n>do action 1\n>do action 3\n>");
	}
	WHEN("test exit method")
	{
		string input = "action1\nexit\naction1";
		istringstream inputStream(input);
		string output;
		ostringstream outputStream(output);

		CMenu menu(inputStream, outputStream);

		menu.AddItem("action1", "do action 1", [&outputStream](istream&) { outputStream << "do action 1" << endl; });
		menu.AddItem("exit", "exit", [&menu](istream&) {menu.Exit(); });

		menu.Run();

		REQUIRE(outputStream.str() == "Commands list:\n"
			"  action1: do action 1\n"
			"  exit: exit\n"
			">do action 1\n>");
	}
	WHEN("test unknown command")
	{
		string input = "action2\n";
		istringstream inputStream(input);
		string output;
		ostringstream outputStream(output);

		CMenu menu(inputStream, outputStream);

		menu.AddItem("action1", "do action 1", [&outputStream](istream&) { outputStream << "do action 1" << endl; });
		menu.Run();
		REQUIRE(outputStream.str() == "Commands list:\n"
			"  action1: do action 1\n"
			">Unknown command\n>");
	}
}

SCENARIO("test editor")
{
	string instructions = "Commands list:\n"
		"  help: Help\n"
		"  exit: Exit\n"
		"  list: Show document\n"
		"  setTitle: Changes title. Args: <new title>\n"
		"  insertParagraph: Insert Paragraph. Args: <position>|end <text>\n"
		"  replaceText: Replace paragraph text. Args: <position> <text>\n"
		"  insertImage: Insert image. Args: <position>|end <width> <height> <path>\n"
		"  resizeImage: Resize Image. Args: <position> <width> <height>\n"
		"  delete: Delete element. Args: <position>\n"
		"  save: Save document. Args: <path>\n"
		"  undo: Undo command\n"
		"  redo: Redo undone command\n";

	WHEN("call help")
	{
		string input = "help\nexit\n";
		istringstream inputStream(input);
		string output;
		ostringstream outputStream(output);
		CEditor editor(inputStream, outputStream);
		editor.Start();
		REQUIRE(outputStream.str() == instructions +
		">" + instructions +
		">");
	}

	WHEN("do action document and call list")
	{
		string input = "insertParagraph end first paragraph\n"
			"insertImage end 100 150 image.jpg\n"
			"setTitle My title\n"
			"list\n";
		istringstream inputStream(input);
		string output;
		ostringstream outputStream(output);
		CEditor editor(inputStream, outputStream);

		editor.Start();
		REQUIRE(outputStream.str() == instructions +
			">>>>-------------\n"
			"Title: My title\n"
			"0. Paragraph:  first paragraph\n"
			"1. Image: 100 150 images\\image(0).jpg\n"
			"-------------\n"
			">");
	}

	WHEN("test delete action")
	{
		string input = "insertParagraph end first paragraph\n"
			"insertImage end 100 150 image.jpg\n"
			"delete 0\n"
			"list\n";
		istringstream inputStream(input);
		string output;
		ostringstream outputStream(output);
		CEditor editor(inputStream, outputStream);

		editor.Start();
		REQUIRE(outputStream.str() == instructions +
			">>>>-------------\n"
			"Title: \n"
			"0. Image: 100 150 images\\image(0).jpg\n"
			"-------------\n"
			">");
	}

	WHEN("replace text")
	{
		string input = "insertParagraph end first paragraph\n"
			"insertParagraph end second paragraph\n"
			"replaceText 1 modified second paragraph\n"
			"list\n";
		istringstream inputStream(input);
		string output;
		ostringstream outputStream(output);
		CEditor editor(inputStream, outputStream);

		editor.Start();
		REQUIRE(outputStream.str() == instructions +
			">>>>-------------\n"
			"Title: \n"
			"0. Paragraph:  first paragraph\n"
			"1. Paragraph:  modified second paragraph\n"
			"-------------\n"
			">");
	}

	WHEN("resize image")
	{
		string input = "insertImage end 100 150 image.jpg\n"
			"resizeImage 0 150 300\n"
			"list\n";
		istringstream inputStream(input);
		string output;
		ostringstream outputStream(output);
		CEditor editor(inputStream, outputStream);

		editor.Start();
		REQUIRE(outputStream.str() == instructions +
			">>>-------------\n"
			"Title: \n"
			"0. Image: 150 300 images\\image(0).jpg\n"
			"-------------\n"
			">");
	}

	WHEN("undo/redo")
	{
		string input = "setTitle My title\n"
			"list\n"
			"undo\n"
			"list\n"
			"redo\n"
			"list\n";
		istringstream inputStream(input);
		string output;
		ostringstream outputStream(output);
		CEditor editor(inputStream, outputStream);

		editor.Start();
		REQUIRE(outputStream.str() == instructions +
			">>-------------\n"
			"Title: My title\n"
			"-------------\n"
			">>-------------\n"
			"Title: \n"
			"-------------\n"
			">>-------------\n"
			"Title: My title\n"
			"-------------\n"
			">");
	}
}
