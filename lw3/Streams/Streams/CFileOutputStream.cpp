#include "CFileOutputStream.h"
#include <string>

using namespace std;

CFileOutputStream::CFileOutputStream(string const& fileName)
{
	m_file.open(fileName, std::ios_base::out | std::ios_base::binary);
	if (!m_file.is_open())
	{
		throw exception("unexpected error in opening file");
	}
}
CFileOutputStream::~CFileOutputStream()
{
	m_file.close();
}


void CFileOutputStream::WriteByte(uint8_t data)
{
	char ch = (char)data;
	if (!m_file.write(&ch, 1))
	{
		throw std::ios_base::failure("Cannot write byte");
	}
}

void CFileOutputStream::WriteBlock(const void* srcData, streamsize size)
{
	if (!m_file.write(static_cast<const char*>(srcData), size))
	{
		throw std::ios_base::failure("Cannot write block");
	}
}
