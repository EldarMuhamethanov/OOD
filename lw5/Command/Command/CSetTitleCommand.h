#pragma once
#include "CAbstractCommand.h"
#include "IDocument.h"
#include <string>

class CSetTitleCommand: public CAbstractCommand
{
public:
	CSetTitleCommand(IDocument& document, const std::string newTitle);

	void DoExecute();
	void DoUnexecute();
	void OnDeleteFrom() override {};
private:
	IDocument& m_document;
	std::string m_oldTitle;
	std::string m_newTitle;
};

