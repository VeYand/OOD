#ifndef CIRCLEDRAWINGSTRATEGY_H
#define CIRCLEDRAWINGSTRATEGY_H
#include "IDrawingStrategy.h"
#include "../Point.h"
#include "../../gfx/ICanvas.h"

#include <sstream>
#include <string>

namespace shapes
{
class CircleDrawingStrategy final : public IDrawingStrategy
{
public:
	CircleDrawingStrategy(
		const Point center,
		const double radius
		)
		: m_center(center), m_radius(radius)
	{
	}

	void Draw(gfx::ICanvas& canvas, Color color) const override
	{
		canvas.SetColor(color);
		canvas.DrawEllipse(m_center.x, m_center.y, m_radius, m_radius);
	}

	void Move(const double dx, const double dy) override
	{
		m_center.x += dx;
		m_center.y += dy;
	}

	[[nodiscard]] std::string ToString() const override
	{
		std::ostringstream oss;
		oss << m_center.x << " " << m_center.y << " " << m_radius;
		return oss.str();
	}

	[[nodiscard]] std::string GetName() const override
	{
		return m_name;
	}

private:
	static constexpr auto m_name = "circle";
	Point m_center;
	double m_radius;
};
}

#endif //CIRCLEDRAWINGSTRATEGY_H