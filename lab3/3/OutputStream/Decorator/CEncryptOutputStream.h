#ifndef CENCRYPTOUTPUTSTREAM_H
#define CENCRYPTOUTPUTSTREAM_H

#include "COutputStreamDecorator.h"
#include "../../EncryptUtils/CByteSubstitutionTable.h"

class CEncryptOutputStream final : public COutputStreamDecorator
{
public:
	CEncryptOutputStream(IOutputDataStreamPtr &&outputStream, const uint32_t key)
		: COutputStreamDecorator(std::move(outputStream)),
		  m_substitutionTable(key)
	{
	}

	void WriteByte(const uint8_t data) override
	{
		const uint8_t encryptedByte = m_substitutionTable.Encrypt(data);
		m_outputStream->WriteByte(encryptedByte);
	}

	void WriteBlock(const void *srcData, const std::streamsize size) override
	{
		const auto *data = static_cast<const uint8_t *>(srcData);
		std::vector<uint8_t> encryptedData(size);
		for (std::streamsize i = 0; i < size; ++i)
		{
			encryptedData[i] = m_substitutionTable.Encrypt(data[i]);
		}
		m_outputStream->WriteBlock(encryptedData.data(), size);
	}

	void Close() override
	{
		m_outputStream->Close();
	}

private:
	CByteSubstitutionTable m_substitutionTable;
};

#endif //CENCRYPTOUTPUTSTREAM_H
