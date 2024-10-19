#ifndef CMEMORYINPUTSTREAM_H
#define CMEMORYINPUTSTREAM_H

#include "IInputDataStream.h"
#include <vector>
#include <stdexcept>
#include <cstring>

class CMemoryInputStream final : public IInputDataStream
{
public:
	explicit CMemoryInputStream(const std::vector<uint8_t> &data)
		: m_data(data), m_position(0)
	{
	}

	[[nodiscard]] bool IsEOF() const override
	{
		AssertStreamOpened();
		return m_position >= m_data.size();
	}

	bool ReadByte(uint8_t &byte) override
	{
		AssertStreamOpened();
		if (IsEOF())
		{
			throw std::ios_base::failure("End of stream");
		}
		byte = m_data[m_position++];
		return true;
	}

	std::streamsize ReadBlock(void *dstBuffer, const std::streamsize size) override
	{
		AssertStreamOpened();
		if (IsEOF())
		{
			throw std::ios_base::failure("End of stream");
		}

		const std::streamsize bytesToRead = std::min(size, static_cast<std::streamsize>(m_data.size() - m_position));
		std::memcpy(dstBuffer, &m_data[m_position], bytesToRead);
		m_position += bytesToRead;
		return bytesToRead;
	}

	void Close() override
	{
		m_closed = true;
	}

private:
	bool m_closed = false;
	std::vector<uint8_t> m_data;
	std::size_t m_position;

	void AssertStreamOpened() const
	{
		if (m_closed)
		{
			throw std::logic_error("Cannot operate on closed stream");
		}
	}
};

#endif //CMEMORYINPUTSTREAM_H
