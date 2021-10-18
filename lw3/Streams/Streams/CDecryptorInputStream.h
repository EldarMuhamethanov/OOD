#pragma once
#include <memory>
#include "IInputDataStream.h"
#include "Encryptor.h"

class CDecryptorInputStream : public IInputDataStream
{
public:
	CDecryptorInputStream(std::unique_ptr<IInputDataStream> stream, std::unique_ptr<Encryptor> encryptor)
		: m_stream(std::move(stream))
		, m_encryptor(std::move(encryptor))
	{}
	bool IsEOF() override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size);
private:
	std::unique_ptr<IInputDataStream> m_stream;
	std::unique_ptr<Encryptor> m_encryptor;
};

