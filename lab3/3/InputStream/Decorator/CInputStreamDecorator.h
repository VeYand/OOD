#ifndef CINPUTSTREAMDECORATOR_H
#define CINPUTSTREAMDECORATOR_H
#include "../IInputDataStream.h"

class CInputStreamDecorator : public IInputDataStream
{
protected:
	explicit CInputStreamDecorator(IInputDataStreamPtr &&inputStream): m_inputStream(std::move(inputStream))
	{
	}

	IInputDataStreamPtr m_inputStream;
};

#endif //CINPUTSTREAMDECORATOR_H
