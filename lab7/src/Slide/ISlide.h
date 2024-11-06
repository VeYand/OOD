#ifndef ISLIDE_H
#define ISLIDE_H

#include "../IDrawable.h"
#include "../Shape/IShapes.h"

class ISlide : public IDrawable
{
public:
	[[nodiscard]] virtual double GetWidth() const = 0;

	[[nodiscard]] virtual double GetHeight() const = 0;

	[[nodiscard]] virtual size_t GetShapesCount() const = 0;

	[[nodiscard]] virtual IShapes &GetShapes() const = 0;

	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;

	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual void GroupShapesAtIndexex(std::vector<size_t> indexes) = 0;

	virtual void InsertShape(const std::shared_ptr<IShape> &shape, size_t position) = 0;

	void Draw(ICanvas &canvas) const override = 0;

	~ISlide() override = default;
};

#endif //ISLIDE_H
