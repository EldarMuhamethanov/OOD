#pragma once
#include "IInputDataStream.h"
#include <fstream>

class CFileInputStream : public IInputDataStream
{
public:
	CFileInputStream(std::string const& fileName);
	~CFileInputStream();
	bool IsEOF() override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::ifstream m_file;
};

