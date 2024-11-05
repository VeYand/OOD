#ifndef CSLIDE_H
#define CSLIDE_H
#include <limits>
#include <memory>

#include "ISlide.h"
#include "../Shape/IShape.h"
#include "../CommonTypes.h"

class CSlide final : public ISlide
{
public:
	[[nodiscard]] double GetWidth() const override;

	[[nodiscard]] double GetHeight() const override;

	[[nodiscard]] IShapes &GetShapes() const override;

	void Draw(ICanvas &canvas) const override;

	/** Хз что ниже */

	[[nodiscard]] size_t GetShapesCount() const;

	std::shared_ptr<IShape> GetShapeAtIndex(size_t index);

	void InsertShape(const std::shared_ptr<IShape> &shape, size_t position = std::numeric_limits<size_t>::max());

	void RemoveShapeAtIndex(size_t index);

	[[nodiscard]] RGBAColor GetBackgroundColor() const;

	void SetBackgroundColor(RGBAColor color);
};

#endif //CSLIDE_H
