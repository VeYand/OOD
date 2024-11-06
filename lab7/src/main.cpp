#include "CommandHandler.h"
#include "Canvas/Canvas.h"
#include "ShapeFactory/ShapeFactory.h"
#include "Slide/CSlide.h"

int main()
{
	std::unique_ptr<ISlide> slide = std::make_unique<CSlide>(800, 600);
	auto canvas = std::make_unique<Canvas>(800, 600);
	const auto rawCanvasPtr = canvas.get();
	std::unique_ptr<IShapeFactory> factory = std::make_unique<ShapeFactory>();

	CommandHandler handler(std::move(slide), std::move(canvas), std::move(factory));
	handler.Run();
	rawCanvasPtr->SaveToFile("output.png");
}
