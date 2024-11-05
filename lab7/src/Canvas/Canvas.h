#ifndef CANVAS_H
#define CANVAS_H

#include "ICanvas.h"

class Canvas final : ICanvas
{
public:
	void EndFill() override
	{
	}

	void MoveTo(double x, double y) override
	{
	}

	void LineTo(double x, double y) override
	{
	}

	void DrawEllipse(double left, double top, double width, double height) override
	{
	}

	void SetLineColor(RGBAColor color) override
	{
	}

	void BeginFill(RGBAColor color) override
	{
	}
};

#endif //CANVAS_H
