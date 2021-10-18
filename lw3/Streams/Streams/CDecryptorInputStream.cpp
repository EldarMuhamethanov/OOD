#include <stdexcept>
#include "CDecryptorInputStream.h"

using namespace std;

bool CDecryptorInputStream::IsEOF()
{
	return m_stream->IsEOF();
}

uint8_t CDecryptorInputStream::ReadByte()
{
	uint8_t byte = m_stream->ReadByte();
	return m_encryptor->Decode(byte);
}

streamsize CDecryptorInputStream::ReadBlock(void* dstBuffer, streamsize size)
{
    auto data = static_cast<uint8_t*>(dstBuffer);

    for (std::streamsize i = 0; i < size; i++)
    {
        try
        {
            *data = ReadByte();
        }
        catch (std::exception&)
        {
            return i + 1;
        }
        data++;
    }

    return size;
}