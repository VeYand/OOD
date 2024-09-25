#ifndef SHAPE_H
#define SHAPE_H
#include "Color.h"
#include "strategy/IFigureStrategy.h"
#include "../gfx/ICanvas.h"
#include <cassert>
#include <memory>

namespace shapes
{
class Shape
{
public:
	Shape(
		const Color color,
		std::unique_ptr<IFigureStrategy>&& strategy
		)
		: m_color(color), m_figureStrategy(std::move(strategy))
	{
		assert(m_figureStrategy);
	}

	void Draw(gfx::ICanvas& canvas) const
	{
		m_figureStrategy->Draw(canvas, m_color);
	}

	void Move(const double dx, const double dy) const
	{
		m_figureStrategy->Move(dx, dy);
	}

	[[nodiscard]] Color GetColor() const
	{
		return m_color;
	}

	void SetColor(const Color color)
	{
		m_color = color;
	}

	[[nodiscard]] std::string GetName() const
	{
		return m_figureStrategy->GetName();
	}

	[[nodiscard]] std::string ToStringStrategy() const
	{
		return m_figureStrategy->ToString();
	}

	void SetDrawingStrategy(std::unique_ptr<IFigureStrategy>&& strategy)
	{
		assert(strategy);
		m_figureStrategy = std::move(strategy);
	}

private:
	Color m_color;
	std::unique_ptr<IFigureStrategy> m_figureStrategy;
};
}
#endif //SHAPE_H