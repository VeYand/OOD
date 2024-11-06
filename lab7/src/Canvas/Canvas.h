#ifndef CANVAS_H
#define CANVAS_H

#include "ICanvas.h"

class Canvas final : public ICanvas
{
public:
	void BeginFill(RGBAColor color) override
	{
	}

	void EndFill() override
	{
	}

	void MoveTo(double x, double y) override
	{
	}

	void LineTo(double x, double y) override
	{
	}

	void DrawEllipse(RectD frame) override
	{
	}

	void DrawPolygon(std::vector<PointD> points) override
	{
	}

	void SetLineColor(std::optional<RGBAColor> color) override
	{
	}
};

#endif //CANVAS_H
