#include "CEncryptorOutputStream.h"

using namespace std;

void CEncryptorOutputStream::WriteByte(uint8_t data)
{
	m_stream->WriteByte(m_encryptor->Encode(data));
}

void CEncryptorOutputStream::WriteBlock(const void* srcData, streamsize size)
{
	auto data = static_cast<const uint8_t*>(srcData);
	for (std::streamsize i = 0; i < size; i++)
	{
		WriteByte(*data);
		data++;
	}
}