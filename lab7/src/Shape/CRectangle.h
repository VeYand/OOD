#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "CShape.h"
#include "../Canvas/ICanvas.h"

class CRectangle final : public CShape
{
public:
	void Draw(ICanvas &canvas) const override;
};

#endif //CRECTANGLE_H
