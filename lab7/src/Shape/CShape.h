#ifndef CSHAPE_H
#define CSHAPE_H

#include "IShape.h"
#include "../CommonTypes.h"
#include "../Canvas/ICanvas.h"

class CShape : IShape
{
public:
	CShape(
		const RectD &frame,
		std::unique_ptr<IStyle> outlineStyle,
		std::unique_ptr<IStyle> fillStyle
	): m_frame(frame),
	   m_outlineStyle(std::move(outlineStyle)),
	   m_fillStyle(std::move(fillStyle))
	{
	}

	[[nodiscard]] RectD GetFrame() const override
	{
		return m_frame;
	}

	void SetFrame(const RectD &rect) override
	{
		m_frame = rect;
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

	std::shared_ptr<IGroupShape> GetGroup() override
	{
		return m_group;
	}

	[[nodiscard]] std::shared_ptr<const IGroupShape> GetGroup() const override
	{
		return m_group;
	}

	void Draw(ICanvas &canvas) const override = 0;

	~CShape() override = default;

private:
	RectD m_frame;
	std::unique_ptr<IStyle> m_outlineStyle;
	std::unique_ptr<IStyle> m_fillStyle;
	std::shared_ptr<IGroupShape> m_group;
};

#endif //CSHAPE_H
