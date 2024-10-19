#ifndef CCOMPRESSOUTPUTSTREAM_H
#define CCOMPRESSOUTPUTSTREAM_H

#include "COutputStreamDecorator.h"

class CCompressOutputStream final : public COutputStreamDecorator
{
public:
	explicit CCompressOutputStream(IOutputDataStreamPtr &&outputStream)
		: COutputStreamDecorator(std::move(outputStream))
	{
	}

	void WriteByte(const uint8_t data) override
	{
		if (data == m_currentByte && m_currentCount < std::numeric_limits<uint8_t>::max())
		{
			m_currentCount++;
		}
		else
		{
			Flush();
			m_currentCount = 1;
			m_currentByte = data;
		}
	}

	void WriteBlock(const void *srcData, const std::streamsize size) override
	{
		if (size == 0) { return; }
		const auto data = static_cast<const uint8_t *>(srcData);

		for (std::streamsize i = 0; i < size; ++i)
		{
			uint8_t currentByte = data[i];

			if (currentByte == m_currentByte && m_currentCount < std::numeric_limits<uint8_t>::max())
			{
				m_currentCount++;
			}
			else
			{
				Flush();
				m_currentCount = 1;
				m_currentByte = currentByte;
			}
		}
	}

	void Close() override
	{
		Flush();
		m_outputStream->Close();
	}

	~CCompressOutputStream() override
	{
		Close();
	}

private:
	uint8_t m_currentByte{};
	int m_currentCount = 0;

	void Flush()
	{
		if (m_currentCount > 0)
		{
			WriteRunLength(m_currentByte, m_currentCount);
			m_currentByte = 0;
			m_currentCount = 0;
		}
	}

	void WriteRunLength(const uint8_t byte, const int count) const
	{
		m_outputStream->WriteByte(static_cast<uint8_t>(count));
		m_outputStream->WriteByte(byte);
	}
};

#endif //CCOMPRESSOUTPUTSTREAM_H
