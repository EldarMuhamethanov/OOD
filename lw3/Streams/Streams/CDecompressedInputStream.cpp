#include "CDecompressedInputStream.h"

using namespace std;

bool CDecompressedInputStream::IsEOF()
{
    return m_stream->IsEOF() || (m_isEof && m_lastByte.count == 0);
}

uint8_t CDecompressedInputStream::ReadByte()
{
    if (IsLastByteEmpty())
    {
        uint8_t* dataOutput = new uint8_t[2];
        streamsize count = m_stream->ReadBlock(dataOutput, 2);

        if (count < 2) {
            m_isEof = true;
        }
        else {
            m_lastByte.count = dataOutput[0];
            m_lastByte.byte = dataOutput[1];
        }
    }

    m_lastByte.count--;

    return m_lastByte.byte;
}

streamsize CDecompressedInputStream::ReadBlock(void* dstBuffer, streamsize size)
{
    auto data = static_cast<uint8_t*>(dstBuffer);

    for (std::streamsize i = 0; i < size; i++)
    {
        try
        {
            *data = ReadByte();
            i++;
        }
        catch (std::exception&)
        {
            return i;
        }
        data++;
    }

    return size;
}

bool CDecompressedInputStream::IsLastByteEmpty()
{
    return m_lastByte.count == 0;
}