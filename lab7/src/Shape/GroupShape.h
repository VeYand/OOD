#ifndef GROUPSHAPE_H
#define GROUPSHAPE_H

#include "IGroupShape.h"

class GroupShape final : public IGroupShape
{
public:
	[[nodiscard]] RectD GetFrame() const override;

	void SetFrame(const RectD &rect) override;

	IStyle &GetOutlineStyle() override;

	[[nodiscard]] const IStyle &GetOutlineStyle() const override;

	IStyle &GetFillStyle() override;

	[[nodiscard]] const IStyle &GetFillStyle() const override;

	[[nodiscard]] size_t GetShapesCount() const override;

	void InsertShape(const std::shared_ptr<IShape> &shape, size_t position) override;

	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;

	void RemoveShapeAtIndex(size_t index) override;

	std::shared_ptr<IGroupShape> GetGroup() override;

	[[nodiscard]] std::shared_ptr<const IGroupShape> GetGroup() const override;

	void Draw(ICanvas &canvas) const override;
};

#endif //GROUPSHAPE_H
