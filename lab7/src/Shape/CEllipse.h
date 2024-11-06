#ifndef CELLIPSE_H
#define CELLIPSE_H

#include "CShape.h"
#include "../Canvas/ICanvas.h"

class CEllipse final : public CShape
{
public:
	CEllipse(
		const RectD &frame,
		std::unique_ptr<IStyle> outlineStyle,
		std::unique_ptr<IStyle> fillStyle
	): CShape(frame, std::move(outlineStyle), std::move(fillStyle))
	{
	}

	void Draw(ICanvas &canvas) const override
	{
	}
};

#endif //CELLIPSE_H
