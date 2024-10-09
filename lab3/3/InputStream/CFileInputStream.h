#ifndef CFILEINPUTSTREAM_H
#define CFILEINPUTSTREAM_H
#include "IInputDataStream.h"

class CFileInputStream final : public IInputDataStream
{
public:
	[[nodiscard]] bool IsEOF() const override;

	uint8_t ReadByte() override;

	std::streamsize ReadBlock(void *dstBuffer, std::streamsize size) override;

	void Close() override;
};

#endif //CFILEINPUTSTREAM_H
