#ifndef CCOMPRESSOUTPUTSTREAM_H
#define CCOMPRESSOUTPUTSTREAM_H

#include "COutputStreamDecorator.h"

class CCompressOutputStream final : public COutputStreamDecorator
{
public:
	explicit CCompressOutputStream(IOutputDataStreamPtr &&outputStream)
		: COutputStreamDecorator(std::move(outputStream)), m_prevByte(0), m_runLength(0)
	{
	}

	void WriteByte(const uint8_t data) override
	{
		if (m_runLength == 0)
		{
			m_prevByte = data;
			m_runLength = 1;
		}
		else if (m_prevByte == data && m_runLength < 255)
		{
			++m_runLength;
		}
		else
		{
			FlushRun();
			m_prevByte = data;
			m_runLength = 1;
		}
	}

	void WriteBlock(const void *srcData, const std::streamsize size) override
	{
		const uint8_t *data = static_cast<const uint8_t *>(srcData);
		for (std::streamsize i = 0; i < size; ++i)
		{
			WriteByte(data[i]);
		}
	}

	void Close() override
	{
		if (m_runLength > 0)
		{
			FlushRun();
		}
		m_outputStream->Close();
	}

private:
	void FlushRun()
	{
		m_outputStream->WriteByte(m_prevByte);
		m_outputStream->WriteByte(m_runLength);
	}

	uint8_t m_prevByte;
	uint8_t m_runLength;
};

#endif //CCOMPRESSOUTPUTSTREAM_H
