#ifndef CFILEOUTPUTSTREAM_H
#define CFILEOUTPUTSTREAM_H
#include <fstream>
#include "IOutputDataStream.h"

class CFileOutputStream final : public IOutputDataStream
{
public:
	explicit CFileOutputStream(const std::string &fileName)
		: m_file(fileName, std::ios::binary)
	{
		if (!m_file.is_open() || m_file.bad())
		{
			throw std::ios_base::failure("Failed to open file");
		}
	}

	void WriteByte(const uint8_t data) override
	{
		AssertStreamOpened();
		const auto byte = static_cast<char>(data);
		if (!m_file.write(&byte, 1) || m_file.bad())
		{
			throw std::ios_base::failure("Failed to write byte");
		}
	}

	void WriteBlock(const void *srcData, const std::streamsize size) override
	{
		AssertStreamOpened();
		if (!m_file.write(static_cast<const char *>(srcData), size) || m_file.bad())
		{
			throw std::ios_base::failure("Failed to write block");
		}
	}

	void Close() override
	{
		if (m_file.is_open())
		{
			m_file.close();
		}
	}

	~CFileOutputStream() override
	{
		Close();
	}

private:
	std::ofstream m_file;

	void AssertStreamOpened() const
	{
		if (!m_file.is_open())
		{
			throw std::logic_error("Cannot operate on closed file");
		}
	}
};

#endif //CFILEOUTPUTSTREAM_H
