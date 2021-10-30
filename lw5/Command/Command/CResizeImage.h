#pragma once
#include "CAbstractCommand.h"
#include "IDocument.h"


class CResizeImage : public CAbstractCommand
{
public:
	CResizeImage(IDocument& document, int position, int newWidth, int newHeight);

	void DoExecute();
	void DoUnexecute();
private:
	IDocument& m_document;
	int m_position;
	int m_newWidth;
	int m_newHeight;
	int m_oldWidth;
	int m_oldHeight;
};

