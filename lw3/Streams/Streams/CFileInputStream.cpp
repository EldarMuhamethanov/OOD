#include "CFileInputStream.h"
#include <fstream>
#include <stdexcept>

using namespace std;

CFileInputStream::CFileInputStream(string const& fileName)
{
	m_file.open(fileName, ios::in | ios::binary);
	if (!m_file.is_open())
	{
		throw exception("unexpected error in opening file");
	}
}

CFileInputStream::~CFileInputStream()
{
	m_file.close();
}

bool CFileInputStream::IsEOF()
{
	return m_file.eof();
}

uint8_t CFileInputStream::ReadByte()
{
	char byte;

	m_file.read(&byte, 1);

	return (uint8_t)byte;
}

streamsize CFileInputStream::ReadBlock(void* dstBuffer, streamsize size)
{
	m_file.read(static_cast<char*>(dstBuffer), size);

	return m_file.gcount();
}