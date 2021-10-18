#pragma once
#include "IOutputDataStream.h"
#include "CFileOutputStream.h"
#include "Encryptor.h"

class CEncryptorOutputStream : public IOutputDataStream
{
public:
	CEncryptorOutputStream(std::unique_ptr<IOutputDataStream> stream, std::unique_ptr<Encryptor> encryptor)
		: m_stream(std::move(stream))
		, m_encryptor(std::move(encryptor))
	{}
	void WriteByte(uint8_t data) override;
	virtual void WriteBlock(const void* srcData, std::streamsize size) override;
private:
	std::unique_ptr<IOutputDataStream> m_stream;
	std::unique_ptr<Encryptor> m_encryptor;
};

