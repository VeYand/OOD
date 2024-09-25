#ifndef LINEDRAWINGSTRATEGY_H
#define LINEDRAWINGSTRATEGY_H
#include "IFigureStrategy.h"
#include "../Point.h"
#include "../../gfx/ICanvas.h"

#include <sstream>
#include <string>

namespace shapes
{
class LineFigureStrategy final : public IFigureStrategy
{
public:
	LineFigureStrategy(
		const Point start,
		const Point end
		)
		: m_start(start), m_end(end)
	{
	}

	void Draw(gfx::ICanvas& canvas, Color color) const override
	{
		canvas.SetColor(color);
		canvas.MoveTo(m_start.x, m_start.y);
		canvas.LineTo(m_end.x, m_end.y);
	}

	void Move(const double dx, const double dy) override
	{
		m_start.x += dx;
		m_start.y += dy;
		m_end.x += dx;
		m_end.y += dy;
	}

	[[nodiscard]] std::string ToString() const override
	{
		std::ostringstream oss;
		oss << m_start.x << " " << m_start.y << " " << m_end.x << " " << m_end.y;
		return oss.str();
	}

	[[nodiscard]] std::string GetName() const override
	{
		return m_name;
	}

private:
	static constexpr auto m_name = "line";
	Point m_start;
	Point m_end;
};
}


#endif //LINEDRAWINGSTRATEGY_H