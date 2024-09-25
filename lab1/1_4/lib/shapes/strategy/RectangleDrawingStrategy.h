#ifndef RECTANGLEDRAWINGSTRATEGY_H
#define RECTANGLEDRAWINGSTRATEGY_H
#include "IFigureStrategy.h"
#include "../Point.h"
#include "../Rect.h"
#include "../../gfx/ICanvas.h"

#include <sstream>

namespace shapes
{
class RectangleDrawingStrategy final : public IFigureStrategy
{
public:
	explicit RectangleDrawingStrategy(
		const Rect& bounds
		)
		: m_bounds(bounds)
	{
	}

	void Draw(gfx::ICanvas& canvas, Color color) const override
	{
		canvas.SetColor(color);
		canvas.MoveTo(m_bounds.leftTop.x, m_bounds.leftTop.y);
		canvas.LineTo(m_bounds.rightBottom.x, m_bounds.leftTop.y);
		canvas.LineTo(m_bounds.rightBottom.x, m_bounds.rightBottom.y);
		canvas.LineTo(m_bounds.leftTop.x, m_bounds.rightBottom.y);
		canvas.LineTo(m_bounds.leftTop.x, m_bounds.leftTop.y);
	}

	void Move(const double dx, const double dy) override
	{
		m_bounds.leftTop.x += dx;
		m_bounds.leftTop.y += dy;
		m_bounds.rightBottom.x += dx;
		m_bounds.rightBottom.y += dy;
	}

	[[nodiscard]] std::string ToString() const override
	{
		std::ostringstream oss;
		oss << m_bounds.leftTop.x << " " << m_bounds.leftTop.y << " " << m_bounds.rightBottom.x - m_bounds.leftTop.x << " " << m_bounds.rightBottom.y - m_bounds.leftTop.y;
		return oss.str();
	}

	[[nodiscard]] std::string GetName() const override
	{
		return m_name;
	}

private:
	static constexpr auto m_name = "rectangle";
	Rect m_bounds;
};
}

#endif //RECTANGLEDRAWINGSTRATEGY_H