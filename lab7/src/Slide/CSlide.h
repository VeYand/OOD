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

	[[nodiscard]] size_t GetShapesCount() const override;

	[[nodiscard]] IShapes &GetShapes() const override;

	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;

	void RemoveShapeAtIndex(size_t index) override;

	void GroupShapesAtIndexex(std::vector<size_t> indexes) override;

	void InsertShape(const std::shared_ptr<IShape> &shape, size_t position) override;

	void Draw(ICanvas &canvas) const override;
};

#endif //CSLIDE_H
