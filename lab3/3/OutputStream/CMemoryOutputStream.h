#ifndef CMEMORYOUTPUTSTREAM_H
#define CMEMORYOUTPUTSTREAM_H
#include "IOutputDataStream.h"

class CMemoryOutputStream final : public IOutputDataStream
{
public:
	void WriteByte(uint8_t data) override;

	void WriteBlock(const void *srcData, std::streamsize size) override;

	void Close() override;
};

#endif //CMEMORYOUTPUTSTREAM_H
