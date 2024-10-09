#ifndef CENCRYPTOUTPUTSTREAM_H
#define CENCRYPTOUTPUTSTREAM_H
#include "COutputStreamDecorator.h"

class CEncryptOutputStream final : public COutputStreamDecorator
{
public:
	explicit CEncryptOutputStream(IOutputDataStreamPtr &&outputStream): COutputStreamDecorator(std::move(outputStream))
	{
	}

	void WriteByte(const uint8_t data) override
	{
		m_outputStream->WriteByte(data);
	}

	void WriteBlock(const void *srcData, const std::streamsize size) override
	{
		m_outputStream->WriteBlock(srcData, size);
	}

	void Close() override
	{
		m_outputStream->Close();
	};
};

#endif //CENCRYPTOUTPUTSTREAM_H
