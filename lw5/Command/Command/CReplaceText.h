#pragma once
#include "CAbstractCommand.h"
#include "IDocument.h"

class CReplaceText: public CAbstractCommand
{
public:
	CReplaceText(IDocument& document, size_t position, std::string const& newText);

	void DoExecute() override;
	void DoUnexecute() override;
	void OnDeleteFrom() override {};
private:
	IDocument& m_document;
	size_t m_position;
	std::string m_newText;
	std::string m_oldText;
};

