#pragma once
#include "IInputDataStream.h"
#include <vector>

class CMemoryInputStream : public IInputDataStream
{
public:
	CMemoryInputStream(std::vector<uint8_t>& vector);
	bool IsEOF() override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
private:
	std::vector<uint8_t>& m_vector;
	int m_top = -1;
};

