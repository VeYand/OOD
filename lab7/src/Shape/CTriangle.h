#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CShape.h"
#include "../Canvas/ICanvas.h"

class CTriangle final : public CShape
{
public:
	void Draw(ICanvas &canvas) const override;
};

#endif //CTRIANGLE_H
