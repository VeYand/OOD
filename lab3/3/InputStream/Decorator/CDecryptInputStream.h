#ifndef CDECRYPTINPUTSTREAM_H
#define CDECRYPTINPUTSTREAM_H

#include "CInputStreamDecorator.h"
#include "../../EncryptUtils/CByteSubstitutionTable.h"

class CDecryptInputStream final : public CInputStreamDecorator
{
public:
	CDecryptInputStream(IInputDataStreamPtr &&inputStream, uint32_t key)
		: CInputStreamDecorator(std::move(inputStream)),
		  m_substitutionTable(key)
	{
	}

	[[nodiscard]] bool IsEOF() const override
	{
		return m_inputStream->IsEOF();
	}

	uint8_t ReadByte() override
	{
		return m_substitutionTable.Decrypt(m_inputStream->ReadByte());
	}

	std::streamsize ReadBlock(void *dstBuffer, const std::streamsize size) override
	{
		const std::streamsize bytesRead = m_inputStream->ReadBlock(dstBuffer, size);
		const auto data = static_cast<uint8_t *>(dstBuffer);
		for (std::streamsize i = 0; i < bytesRead; ++i)
		{
			data[i] = m_substitutionTable.Decrypt(data[i]);
		}
		return bytesRead;
	}

	void Close() override
	{
		m_inputStream->Close();
	}

private:
	CByteSubstitutionTable m_substitutionTable;
};

#endif //CDECRYPTINPUTSTREAM_H
