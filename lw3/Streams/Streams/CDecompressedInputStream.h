#pragma once
#include "IInputDataStream.h"

class CDecompressedInputStream : public IInputDataStream
{
	struct LastByteData {
		uint8_t byte = 0;
		uint8_t count = 0;
	};
public:
	CDecompressedInputStream(std::unique_ptr<IInputDataStream> stream)
		: m_stream(std::move(stream))
	{}
	bool IsEOF() override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;
	bool IsLastByteEmpty();
private:
	std::unique_ptr<IInputDataStream> m_stream;
	bool m_isEof = false;
	LastByteData m_lastByte;
};

