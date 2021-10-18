#pragma once
#include "IOutputDataStream.h"
#include <fstream>

class CFileOutputStream: public IOutputDataStream
{
public:
	CFileOutputStream(std::string const& fileName);
	~CFileOutputStream();
	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;
private:
	std::ofstream m_file;
};

