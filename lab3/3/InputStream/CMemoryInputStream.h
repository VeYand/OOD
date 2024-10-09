#ifndef CMEMORYINPUTSTREAM_H
#define CMEMORYINPUTSTREAM_H
#include "IInputDataStream.h"

class CMemoryInputStream final : public IInputDataStream
{
public:
	[[nodiscard]] bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void *dstBuffer, std::streamsize size) override;

	void Close() override;
};

#endif //CMEMORYINPUTSTREAM_H
