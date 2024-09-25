#ifndef IFIGURESTRATEGY_H
#define IFIGURESTRATEGY_H
#include "../Color.h"
#include "../../gfx/ICanvas.h"

namespace shapes
{
class IFigureStrategy
{
public:
	virtual ~IFigureStrategy() = default;

	virtual void Draw(gfx::ICanvas& canvas, Color color) const = 0;

	virtual void Move(double dx, double dy) = 0;

	[[nodiscard]] virtual std::string ToString() const = 0;

	[[nodiscard]] virtual std::string GetName() const = 0;
};
}

#endif //IFIGURESTRATEGY_H