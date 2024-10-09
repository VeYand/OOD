#ifndef CDECOMPRESSINPUTSTREAM_H
#define CDECOMPRESSINPUTSTREAM_H

#include "CInputStreamDecorator.h"

class CDecompressInputStream final : public CInputStreamDecorator
{
public:
	explicit CDecompressInputStream(IInputDataStreamPtr &&inputStream)
		: CInputStreamDecorator(std::move(inputStream)), m_runLength(0)
	{
	}

	[[nodiscard]] bool IsEOF() const override
	{
		return m_runLength == 0 && m_inputStream->IsEOF();
	}

	uint8_t ReadByte() override
	{
		if (m_runLength == 0)
		{
			m_currentByte = m_inputStream->ReadByte();
			m_runLength = m_inputStream->ReadByte();
		}
		--m_runLength;
		return m_currentByte;
	}

	std::streamsize ReadBlock(void *dstBuffer, const std::streamsize size) override
	{
		auto *buffer = static_cast<uint8_t *>(dstBuffer);
		for (std::streamsize i = 0; i < size; ++i)
		{
			if (IsEOF())
			{
				return i;
			}
			buffer[i] = ReadByte();
		}
		return size;
	}

	void Close() override
	{
		m_inputStream->Close();
	}

private:
	uint8_t m_currentByte{};
	uint8_t m_runLength;
};

#endif //CDECOMPRESSINPUTSTREAM_H
