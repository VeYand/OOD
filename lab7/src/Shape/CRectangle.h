#ifndef CRECTANGLE_H
#define CRECTANGLE_H

#include "CShape.h"
#include "../Canvas/ICanvas.h"

class CRectangle final : public CShape
{
public:
	CRectangle(
		const RectD &frame,
		std::unique_ptr<IStyle> outlineStyle,
		std::unique_ptr<IStyle> fillStyle
	): CShape(frame, std::move(outlineStyle), std::move(fillStyle))
	{
	}

	void Draw(ICanvas &canvas) const override;
};

#endif //CRECTANGLE_H
