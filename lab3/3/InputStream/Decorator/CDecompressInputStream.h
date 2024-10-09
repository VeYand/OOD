#ifndef CDECOMPRESSINPUTSTREAM_H
#define CDECOMPRESSINPUTSTREAM_H
#include "CInputStreamDecorator.h"

class CDecompressInputStream final : public CInputStreamDecorator
{
public:
	explicit CDecompressInputStream(IInputDataStreamPtr &&inputStream): CInputStreamDecorator(std::move(inputStream))
	{
	}

	[[nodiscard]] bool IsEOF() const override
	{
		return m_inputStream->IsEOF();
	}

	uint8_t ReadByte() override
	{
		return m_inputStream->ReadByte();
	}

	std::streamsize ReadBlock(void *dstBuffer, const std::streamsize size) override
	{
		return m_inputStream->ReadBlock(dstBuffer, size);
	}

	void Close() override
	{
		m_inputStream->Close();
	}
};

#endif //CDECOMPRESSINPUTSTREAM_H
