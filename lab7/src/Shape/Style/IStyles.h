#ifndef ISTYLES_H
#define ISTYLES_H

#include "IStyle.h"

class IStyles
{
public:
	virtual void InsertStyle(IStyle &style, size_t position) = 0;

	virtual void RemoveStyleAtIndex(size_t index) = 0;

	virtual ~IStyles() = default;
};

#endif //ISTYLES_H
