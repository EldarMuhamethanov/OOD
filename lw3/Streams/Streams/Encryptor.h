#pragma once
#include <cstdint>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

class Encryptor
{
public:
	Encryptor(int key);
	uint8_t Encode(uint8_t value) const;
	uint8_t Decode(uint8_t value) const;
private:
	int m_key;
	std::vector<uint8_t> m_encryptList;
	std::vector<uint8_t> m_decryptMap;
};

