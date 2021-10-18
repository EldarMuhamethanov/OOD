#include "CCompressedOutputStream.h"

using namespace std;

void CCompressedOutputStream::WriteByte(uint8_t byte)
{
	if (IsLastByteEmpty())
	{
		m_lastByte = { byte , 1};
		return;
	}
	if (m_lastByte.byte == byte && m_lastByte.count < 254)
	{
		m_lastByte.count++;
		return;
	}
	m_stream->WriteByte((uint8_t)m_lastByte.count);
	m_stream->WriteByte(m_lastByte.byte);

	m_lastByte = { byte, 1 };
}

CCompressedOutputStream::~CCompressedOutputStream()
{
	if (!IsLastByteEmpty())
	{
		m_stream->WriteByte((uint8_t)m_lastByte.count);
		m_stream->WriteByte(m_lastByte.byte);
	}
}

void CCompressedOutputStream::WriteBlock(const void* srcData, streamsize size)
{
	auto data = static_cast<const uint8_t*>(srcData);
	for (std::streamsize i = 0; i < size; i++)
	{
		WriteByte(*data);
		data++;
	}
}

bool CCompressedOutputStream::IsLastByteEmpty()
{
	return m_lastByte.count == 0;
}