#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include "CShape.h"
#include "../Canvas/ICanvas.h"

class CTriangle final : public CShape
{
public:
	CTriangle(
		const RectD &frame,
		std::unique_ptr<IStyle> outlineStyle,
		std::unique_ptr<IStyle> fillStyle
	): CShape(frame, std::move(outlineStyle), std::move(fillStyle))
	{
	}

	void Draw(ICanvas &canvas) const override;
};

#endif //CTRIANGLE_H
