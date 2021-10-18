#pragma once
#include "CAbstractCommand.h"
#include "CImagesStorage.h"
#include "IDocument.h"

class CInsertImage: public CAbstractCommand
{
public:
	CInsertImage(IDocument& document, const std::string& path, int width, int height, const size_t position);

	void DoExecute();
	void DoUnexecute();
	void OnDeleteFrom() override;
private:
	IDocument& m_document;
	std::string m_path;
	std::string m_newPath;
	int m_width;
	int m_height;
	size_t m_position;
};

