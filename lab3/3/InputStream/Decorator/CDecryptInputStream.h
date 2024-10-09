#ifndef CDECRYPTINPUTSTREAM_H
#define CDECRYPTINPUTSTREAM_H
#include "CInputStreamDecorator.h"

class CDecryptInputStream final : public CInputStreamDecorator
{
public:
	explicit CDecryptInputStream(IInputDataStreamPtr &&inputStream): CInputStreamDecorator(std::move(inputStream))
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

#endif //CDECRYPTINPUTSTREAM_H
