#ifndef CBYTESUBSTITUTIONTABLE_H
#define CBYTESUBSTITUTIONTABLE_H

#include <random>
#include <vector>
#include <algorithm>

class CByteSubstitutionTable
{
public:
	explicit CByteSubstitutionTable(const uint32_t key)
	{
		m_encryptionTable.resize(256);
		std::iota(m_encryptionTable.begin(), m_encryptionTable.end(), 0);

		std::mt19937 generator(key);

		std::ranges::shuffle(m_encryptionTable, generator);

		m_decryptionTable.resize(256);
		for (size_t i = 0; i < 256; ++i)
		{
			m_decryptionTable[m_encryptionTable[i]] = static_cast<uint8_t>(i);
		}
	}

	[[nodiscard]] uint8_t Encrypt(const uint8_t byte) const
	{
		return m_encryptionTable[byte];
	}

	[[nodiscard]] uint8_t Decrypt(const uint8_t byte) const
	{
		return m_decryptionTable[byte];
	}

private:
	std::vector<uint8_t> m_encryptionTable;
	std::vector<uint8_t> m_decryptionTable;
};


#endif //CBYTESUBSTITUTIONTABLE_H
