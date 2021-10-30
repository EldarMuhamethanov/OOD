#include "CMemoryInputStream.h"

using namespace std;

CMemoryInputStream::CMemoryInputStream(vector<uint8_t>& vector)
	: m_vector(vector)
{}

bool CMemoryInputStream::IsEOF()
{
	return m_top >= (int)m_vector.size();
}

uint8_t CMemoryInputStream::ReadByte()
{
	m_top++;
	if (!IsEOF())
	{
		uint8_t byte = m_vector[m_top];
		return byte;
	}
	return '\0';
}

streamsize CMemoryInputStream::ReadBlock(void* dstBuffer, streamsize size)
{
	auto it = static_cast<uint8_t*>(dstBuffer);
	streamsize readedElements = 1;
	uint8_t ch = ReadByte();
	while (!IsEOF() && readedElements < size)
	{
		*it = ch;
		it++;
		readedElements++;
		ch = ReadByte();
	}
	*it = ch;
	return readedElements;
}