#ifndef TRIANGLEDRAWINGSTRATEGY_H
#define TRIANGLEDRAWINGSTRATEGY_H
#include "IFigureStrategy.h"
#include "../Point.h"
#include "../../gfx/ICanvas.h"

#include <sstream>

namespace shapes
{
class TriangleFigureStrategy final : public IFigureStrategy
{
public:
	TriangleFigureStrategy(
		const Point firstAngle,
		const Point secondAngle,
		const Point thirdAngle
		)
		: m_firstAngle(firstAngle), m_secondAngle(secondAngle), m_thirdAngle(thirdAngle)
	{
	}

	void Draw(gfx::ICanvas& canvas, const Color color) const override
	{
		canvas.SetColor(color);
		canvas.MoveTo(m_firstAngle.x, m_firstAngle.y);
		canvas.LineTo(m_secondAngle.x, m_secondAngle.y);
		canvas.LineTo(m_thirdAngle.x, m_thirdAngle.y);
		canvas.LineTo(m_firstAngle.x, m_thirdAngle.y);
	}

	void Move(const double dx, const double dy) override
	{
		m_firstAngle.x += dx;
		m_firstAngle.y += dy;
		m_secondAngle.x += dx;
		m_secondAngle.y += dy;
		m_thirdAngle.x += dx;
		m_thirdAngle.y += dy;
	}

	[[nodiscard]] std::string ToString() const override
	{
		std::ostringstream oss;
		oss << m_firstAngle.x << " "
			<< m_firstAngle.y << " "
			<< m_secondAngle.x << " "
			<< m_secondAngle.y << " "
			<< m_thirdAngle.x << " "
			<< m_thirdAngle.y;
		return oss.str();
	}

	[[nodiscard]] std::string GetName() const override
	{
		return m_name;
	}

private:
	static constexpr auto m_name = "triangle";
	Point m_firstAngle;
	Point m_secondAngle;
	Point m_thirdAngle;
};
}

#endif //TRIANGLEDRAWINGSTRATEGY_H