#ifndef CMEMORYINPUTSTREAM_H
#define CMEMORYINPUTSTREAM_H

#include "IInputDataStream.h"
#include <vector>
#include <stdexcept>
#include <cstring>

class CMemoryInputStream final : public IInputDataStream
{
public:
	CMemoryInputStream(const uint8_t *data, const std::size_t size)
		: m_data(data, data + size), m_position(0)
	{
	}

	[[nodiscard]] bool IsEOF() const override
	{
		return m_position >= m_data.size();
	}

	uint8_t ReadByte() override
	{
		if (IsEOF())
		{
			throw std::runtime_error("End of stream");
		}

		return m_data[m_position++];
	}

	std::streamsize ReadBlock(void *dstBuffer, const std::streamsize size) override
	{
		if (IsEOF())
		{
			throw std::runtime_error("End of stream");
		}

		const std::streamsize bytesToRead = std::min(size, static_cast<std::streamsize>(m_data.size() - m_position));
		std::memcpy(dstBuffer, &m_data[m_position], bytesToRead);
		m_position += bytesToRead;
		return bytesToRead;
	}

	void Close() override
	{
		m_data.clear();
		m_position = 0;
	}

private:
	std::vector<uint8_t> m_data;
	std::size_t m_position;
};

#endif //CMEMORYINPUTSTREAM_H
