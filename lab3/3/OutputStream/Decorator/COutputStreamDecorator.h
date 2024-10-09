#ifndef COUTPUTSTREAMDECORATOR_H
#define COUTPUTSTREAMDECORATOR_H
#include "../IOutputDataStream.h"

class COutputStreamDecorator : public IOutputDataStream
{
protected:
	explicit COutputStreamDecorator(IOutputDataStreamPtr &&outputStream): m_outputStream(std::move(outputStream))
	{
	}

	IOutputDataStreamPtr m_outputStream;
};

#endif //COUTPUTSTREAMDECORATOR_H
