#ifndef GROUPSHAPE_H
#define GROUPSHAPE_H

#include <limits>
#include "IGroupShape.h"
#include "Style/GroupStyle.h"

class GroupShape final : public IGroupShape
{
public:
	[[nodiscard]] RectD GetFrame() const override
	{
		if (m_shapes.empty())
		{
			return {0, 0, 0, 0};
		}

		double leftSum = std::numeric_limits<double>::max();
		double topSum = std::numeric_limits<double>::max();
		double rightSum = std::numeric_limits<double>::lowest();
		double bottomSum = std::numeric_limits<double>::lowest();

		for (const auto &shape: m_shapes)
		{
			auto [left, top, width, height] = shape->GetFrame();
			leftSum = std::min(leftSum, left);
			topSum = std::min(topSum, top);
			rightSum = std::max(rightSum, left + width);
			bottomSum = std::max(bottomSum, top + height);
		}

		return {leftSum, topSum, rightSum - leftSum, bottomSum - topSum};
	}

	void SetFrame(const RectD &rect) override
	{
		auto [left, top, width, height] = GetFrame();
		const double scaleX = rect.width / width;
		const double scaleY = rect.height / height;

		for (const auto &shape: m_shapes)
		{
			const RectD shapeFrame = shape->GetFrame();
			const double newLeft = rect.left + (shapeFrame.left - left) * scaleX;
			const double newTop = rect.top + (shapeFrame.top - top) * scaleY;
			const double newWidth = shapeFrame.width * scaleX;
			const double newHeight = shapeFrame.height * scaleY;
			shape->SetFrame({newLeft, newTop, newWidth, newHeight});
		}
	}

	IStyle &GetOutlineStyle() override
	{
		return *m_outlineStyle;
	}

	[[nodiscard]] IStyle &GetOutlineStyle() const override
	{
		return *m_outlineStyle;
	}

	IStyle &GetFillStyle() override
	{
		return *m_fillStyle;
	}

	[[nodiscard]] IStyle &GetFillStyle() const override
	{
		return *m_fillStyle;
	}

	[[nodiscard]] size_t GetShapesCount() const override
	{
		return m_shapes.size();
	}

	void InsertShape(const std::shared_ptr<IShape> &shape, size_t position) override
	{
		if (position > m_shapes.size())
		{
			position = m_shapes.size();
		}
		m_shapes.insert(m_shapes.begin() + static_cast<std::vector<int>::difference_type>(position), shape);
		m_fillStyle->InsertStyle(shape->GetFillStyle(), position);
		m_outlineStyle->InsertStyle(shape->GetOutlineStyle(), position);
	}

	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override
	{
		if (index >= m_shapes.size())
		{
			throw std::out_of_range("Index is out of range");
		}
		return m_shapes[index];
	}

	void RemoveShapeAtIndex(size_t index) override
	{
		if (index >= m_shapes.size())
		{
			throw std::out_of_range("Index is out of range");
		}
		m_shapes.erase(m_shapes.begin() + static_cast<std::vector<int>::difference_type>(index));
		m_fillStyle->RemoveStyleAtIndex(index);
		m_outlineStyle->RemoveStyleAtIndex(index);
	}

	void Draw(ICanvas &canvas) const override
	{
		for (const auto &shape: m_shapes)
		{
			shape->Draw(canvas);
		}
	}

private:
	std::vector<std::shared_ptr<IShape> > m_shapes;
	std::unique_ptr<IGroupStyle> m_outlineStyle = std::make_unique<GroupStyle>();
	std::unique_ptr<IGroupStyle> m_fillStyle = std::make_unique<GroupStyle>();
};

#endif //GROUPSHAPE_H
