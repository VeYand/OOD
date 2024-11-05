#ifndef CSHAPE_H
#define CSHAPE_H

#include "IShape.h"
#include "../CommonTypes.h"
#include "../Canvas/ICanvas.h"

class CShape : IShape
{
public:
	RectD GetFrame() override;

	void SetFrame(const RectD &rect) override;

	IStyle &GetOutlineStyle() override;

	[[nodiscard]] const IStyle &GetOutlineStyle() const override;

	IStyle &GetFillStyle() override;

	[[nodiscard]] const IStyle &GetFillStyle() const override;

	std::shared_ptr<IGroupShape> GetGroup() override;

	[[nodiscard]] std::shared_ptr<const IGroupShape> GetGroup() const override;

	virtual void Draw(ICanvas &canvas) const = 0;

	~CShape() override = default;
};

#endif //CSHAPE_H
