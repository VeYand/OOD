#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"
#include "Color.h"
#include "Rect.h"
#include "Shape.h"

class Rectangle final : public Shape
{
public:
	Rectangle(const Color color, const Rect& bounds) : Shape(color), m_bounds(bounds)
	{
	}

	void Draw(gfx::ICanvas &canvas) const override
	{
		canvas.SetColor(GetColor());
		canvas.MoveTo(m_bounds.leftTop.x, m_bounds.leftTop.y);
		canvas.LineTo(m_bounds.rightBottom.x, m_bounds.leftTop.y);
		canvas.LineTo(m_bounds.rightBottom.x, m_bounds.rightBottom.y);
		canvas.LineTo(m_bounds.leftTop.x, m_bounds.rightBottom.y);
		canvas.LineTo(m_bounds.leftTop.x, m_bounds.leftTop.y);
	}

	[[nodiscard]] Point GetLeftTop() const
	{
		return m_leftTop;
	}

	[[nodiscard]] double GetWidth() const
	{
		return m_bounds.rightBottom.x - m_bounds.leftTop.x;
	}

	[[nodiscard]] double GetHeight() const
	{
		return m_bounds.leftTop.y - m_bounds.rightBottom.y;
	}

private:
	Point m_leftTop;
	Rect m_bounds;
};

#endif //RECTANGLE_H
