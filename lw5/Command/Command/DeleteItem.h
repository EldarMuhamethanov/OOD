#pragma once
#include "CAbstractCommand.h"
#include "IDocument.h"
#include <memory>


class CDeleteItem : public CAbstractCommand
{
public:
	CDeleteItem(IDocument& document, size_t position);

	void DoExecute();
	void DoUnexecute();
	void OnDeleteFrom() override {};
private:
	IDocument& m_document;
	size_t m_position;
	CDocumentItem* m_oldItem = nullptr;
};

