#ifndef CMEMORYOUTPUTSTREAM_H
#define CMEMORYOUTPUTSTREAM_H

#include "IOutputDataStream.h"
#include <vector>
#include <stdexcept>

class CMemoryOutputStream final : public IOutputDataStream
{
public:
	CMemoryOutputStream() = default;

	void WriteByte(const uint8_t data) override
	{
		AssertFileOpened();
		m_data.push_back(data);
	}

	void WriteBlock(const void *srcData, const std::streamsize size) override
	{
		AssertFileOpened();
		const auto *byteData = static_cast<const uint8_t *>(srcData);
		m_data.insert(m_data.end(), byteData, byteData + size);
	}

	void Close() override
	{
		m_data.clear();
		m_closed = true;
	}

private:
	bool m_closed = false;
	std::vector<uint8_t> m_data;

	void AssertFileOpened() const
	{
		if (m_closed)
		{
			throw std::logic_error("Cannot operate on closed stream");
		}
	}
};

#endif //CMEMORYOUTPUTSTREAM_H
