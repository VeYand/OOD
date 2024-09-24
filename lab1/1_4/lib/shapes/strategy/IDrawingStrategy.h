#ifndef IDRAWINGSTRATEGY_H
#define IDRAWINGSTRATEGY_H
#include "../Color.h"
#include "../../gfx/ICanvas.h"

namespace shapes
{
class IDrawingStrategy
{
public:
	virtual ~IDrawingStrategy() = default;

	virtual void Draw(gfx::ICanvas& canvas, Color color) const = 0;

	virtual void Move(double dx, double dy) = 0;

	[[nodiscard]] virtual std::string ToString() const = 0;

	[[nodiscard]] virtual std::string GetName() const = 0;
};
}

#endif //IDRAWINGSTRATEGY_H