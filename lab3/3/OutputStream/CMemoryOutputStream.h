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
		m_data.push_back(data);
	}

	void WriteBlock(const void *srcData, const std::streamsize size) override
	{
		const auto *byteData = static_cast<const uint8_t *>(srcData);
		m_data.insert(m_data.end(), byteData, byteData + size);
	}

	void Close() override
	{
		m_data.clear();
	}

	[[nodiscard]] const std::vector<uint8_t> &GetData() const
	{
		return m_data;
	}

private:
	std::vector<uint8_t> m_data;
};

#endif //CMEMORYOUTPUTSTREAM_H
