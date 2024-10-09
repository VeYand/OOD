#ifndef IDESIGNER_H
#define IDESIGNER_H

#include "PictureDraft.h"

class IDesigner
{
public:
	virtual ~IDesigner() = default;

	virtual PictureDraft CreateDraft(std::istream &inputData) = 0;
};

#endif //IDESIGNER_H
