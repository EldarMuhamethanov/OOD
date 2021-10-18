#pragma once
#include "CAbstractCommand.h"
#include "IDocument.h"

class CInsertParagraph : public CAbstractCommand
{
public:
	CInsertParagraph(IDocument& document, std::string const& text, int position);

	void DoExecute();
	void DoUnexecute();
	void OnDeleteFrom() override {};
private:
	IDocument& m_document;
	std::string m_text;
	int m_position;
};

