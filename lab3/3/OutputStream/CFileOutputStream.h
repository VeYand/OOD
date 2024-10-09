#ifndef CFILEOUTPUTSTREAM_H
#define CFILEOUTPUTSTREAM_H
#include "IOutputDataStream.h"

class CFileOutputStream final : public IOutputDataStream
{
public:
	void WriteByte(uint8_t data) override;

	void WriteBlock(const void *srcData, std::streamsize size) override;

	void Close() override;
};

#endif //CFILEOUTPUTSTREAM_H
