#ifndef CFILEINPUTSTREAM_H
#define CFILEINPUTSTREAM_H
#include <fstream>
#include "IInputDataStream.h"

class CFileInputStream final : public IInputDataStream
{
public:
	explicit CFileInputStream(const std::string &fileName)
		: m_file(fileName, std::ios::binary)
	{
		if (!m_file.is_open() || m_file.bad())
		{
			throw std::invalid_argument("Failed to open file");
		}
	}

	[[nodiscard]] bool IsEOF() const override
	{
		return m_file.eof();
	}

	uint8_t ReadByte() override
	{
		char byte;
		m_file.read(&byte, 1);
		if (m_file.bad())
		{
			throw std::runtime_error("Failed to read file");
		}

		return byte;
	}

	std::streamsize ReadBlock(void *dstBuffer, const std::streamsize size) override
	{
		m_file.read(static_cast<char *>(dstBuffer), size);
		if (m_file.bad())
		{
			throw std::runtime_error("Failed to read file");
		}
		return m_file.gcount();
	}

	void Close() override
	{
		if (m_file.is_open())
		{
			m_file.close();
		}
	}

	~CFileInputStream() override
	{
		Close();
	}

private:
	std::ifstream m_file;
};

#endif //CFILEINPUTSTREAM_H
