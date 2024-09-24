#ifndef SHAPE_H
#define SHAPE_H
#include "Color.h"
#include "strategy/IDrawingStrategy.h"
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
		std::unique_ptr<IDrawingStrategy>&& strategy
		)
		: m_color(color), m_drawingStrategy(std::move(strategy))
	{
		assert(m_drawingStrategy);
	}

	void Draw(gfx::ICanvas& canvas) const
	{
		m_drawingStrategy->Draw(canvas, m_color);
	}

	void Move(const double dx, const double dy) const
	{
		m_drawingStrategy->Move(dx, dy);
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
		return m_drawingStrategy->GetName();
	}

	[[nodiscard]] std::string ToStringStrategy() const
	{
		return m_drawingStrategy->ToString();
	}

	void SetDrawingStrategy(std::unique_ptr<IDrawingStrategy>&& strategy)
	{
		assert(strategy);
		m_drawingStrategy = std::move(strategy);
	}

private:
	Color m_color;
	std::unique_ptr<IDrawingStrategy> m_drawingStrategy;
};
}
#endif //SHAPE_H