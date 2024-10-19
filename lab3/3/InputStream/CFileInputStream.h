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
			throw std::ios_base::failure("Failed to open file");
		}
	}

	[[nodiscard]] bool IsEOF() const override
	{
		AssertStreamOpened();
		return m_file.eof();
	}

	bool ReadByte(uint8_t& byte) override
	{
		AssertStreamOpened();
		char byte2;
		m_file.read(&byte2, sizeof(byte));

		if (IsEOF())
		{
			return false;
		}

		if (m_file.bad())
		{
			throw std::ios_base::failure("Failed to read file");
		}

		byte = byte2;
		return true;
	}

	std::streamsize ReadBlock(void *dstBuffer, const std::streamsize size) override
	{
		AssertStreamOpened();
		m_file.read(static_cast<char *>(dstBuffer), size);
		if (m_file.bad())
		{
			throw std::ios_base::failure("Failed to read file");
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

	void AssertStreamOpened() const
	{
		if (!m_file.is_open())
		{
			throw std::logic_error("Cannot operate on closed file");
		}
	}
};

#endif //CFILEINPUTSTREAM_H
