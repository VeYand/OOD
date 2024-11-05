#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "CShape.h"
#include "../Canvas/ICanvas.h"

class CEllipse final : public CShape
{
public:
	void Draw(ICanvas &canvas) const override;
};

#endif //CELLIPSE_H
