#pragma once
#include <memory>
#include "IOutputDataStream.h"

class CCompressedOutputStream: public IOutputDataStream
{
	struct LastByteData {
		uint8_t byte = 0;
		uint8_t count = 0;
	};
public:
	CCompressedOutputStream(std::unique_ptr<IOutputDataStream> stream)
		: m_stream(move(stream))
	{}
	~CCompressedOutputStream();
	void WriteByte(uint8_t byte) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;
	bool IsLastByteEmpty();
private:
	std::unique_ptr<IOutputDataStream> m_stream;
	LastByteData m_lastByte;
};

