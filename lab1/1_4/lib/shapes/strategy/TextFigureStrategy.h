#ifndef TEXTDRAWINGSTRATEGY_H
#define TEXTDRAWINGSTRATEGY_H
#include "IFigureStrategy.h"
#include "../Point.h"
#include "../../gfx/ICanvas.h"

#include <sstream>

namespace shapes
{
class TextFigureStrategy final : public IFigureStrategy
{
public:
	TextFigureStrategy(
		const Point leftTop,
		const double font,
		std::string text
		)
		: m_leftTop(leftTop), m_font(font), m_text(std::move(text))
	{
	}

	void Draw(gfx::ICanvas& canvas, Color color) const override
	{
		canvas.SetColor(color);
		canvas.DrawText(m_leftTop.x, m_leftTop.y, m_font, m_text);
	}

	void Move(const double dx, const double dy) override
	{
		m_leftTop.x += dx;
		m_leftTop.y += dy;
	}

	[[nodiscard]] std::string ToString() const override
	{
		std::ostringstream oss;
		oss << m_leftTop.x << " " << m_leftTop.y << " " << m_font << " " << m_text;
		return oss.str();
	}

	[[nodiscard]] std::string GetName() const override
	{
		return m_name;
	}

private:
	static constexpr auto m_name = "text";
	Point m_leftTop;
	double m_font;
	std::string m_text;
};
};

#endif //TEXTDRAWINGSTRATEGY_H