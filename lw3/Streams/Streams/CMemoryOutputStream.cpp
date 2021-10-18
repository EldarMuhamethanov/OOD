#include "CMemoryOutputStream.h"

using namespace std;

CMemoryOutputStream::CMemoryOutputStream(vector<uint8_t>& vector)
	: m_vector(vector)
{}

void CMemoryOutputStream::WriteByte(uint8_t data)
{
	m_vector.push_back(data);
}

void CMemoryOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
    auto it = static_cast<const uint8_t*>(srcData);
    for (streamsize i = 0; i < size; i++)
    {
        WriteByte(*it);
        it++;
    }
}