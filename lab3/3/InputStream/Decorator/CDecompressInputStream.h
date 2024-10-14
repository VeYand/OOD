#ifndef CDECOMPRESSINPUTSTREAM_H
#define CDECOMPRESSINPUTSTREAM_H

#include "CInputStreamDecorator.h"

class CDecompressInputStream final : public CInputStreamDecorator
{
public:
	explicit CDecompressInputStream(IInputDataStreamPtr &&inputStream)
		: CInputStreamDecorator(std::move(inputStream))
	{
	}

	[[nodiscard]] bool IsEOF() override
	{
		return m_inputStream->IsEOF();
	}

	uint8_t ReadByte() override
	{
		uint8_t byte;
		ReadDecompressedByte(byte);
		return byte;
	}

	std::streamsize ReadBlock(void *dstBuffer, const std::streamsize size) override
	{
		const auto buffer = static_cast<uint8_t *>(dstBuffer);

		std::streamsize readedBytes = 0;
		for (;readedBytes < size; ++readedBytes)
		{
			uint8_t byte;
			if (m_currentCount <= 0 && m_inputStream->IsEOF() || !ReadDecompressedByte(byte))
			{
				break;
			}

			buffer[readedBytes] = byte;
		}

		return readedBytes;
	}

	void Close() override
	{
		m_inputStream->Close();
	}

private:
	uint8_t m_currentByte{};
	int m_currentCount = 0;
	int m_readCount = 0;

	bool ReadDecompressedByte(uint8_t& byte)
	{
		if (m_currentCount <= 0)
		{
			uint8_t buffer[2];
			const auto readedCount = m_inputStream->ReadBlock(buffer, sizeof(buffer));
			if (sizeof(buffer) != readedCount)
			{
				return false;
			}

			m_currentCount = static_cast<int>(buffer[0]);
			m_currentByte = buffer[1];
		}

		m_currentCount--;

		byte = m_currentByte;
		return true;
	}
};

#endif //CDECOMPRESSINPUTSTREAM_H
