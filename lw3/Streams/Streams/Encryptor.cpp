#include "Encryptor.h"

using namespace std;

Encryptor::Encryptor(int key)
	: m_key(key)
{
	std::vector<uint8_t> encryptList(256);
	std::vector<uint8_t> decryptList(256);

	for (size_t i = 0; i < 256; i++)
		encryptList[i] = (uint8_t)i;

	std::shuffle(encryptList.begin(), encryptList.end(), std::default_random_engine(key));
	
	for (size_t i = 0; i < 256; i++)
		decryptList[(int)encryptList[i]] = (uint8_t)i;

	m_encryptList = encryptList;
	m_decryptMap = decryptList;
}

uint8_t Encryptor::Encode(uint8_t value) const
{
	return m_encryptList[value];
}

uint8_t Encryptor::Decode(uint8_t value) const
{
	return m_decryptMap.at(value);
}