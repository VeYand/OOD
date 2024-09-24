#include "lib/gfx/PNGCanvas.h"
#include "lib/service/ShapeService.h"

#include <cstdlib>
#include <iostream>

constexpr int CANVAS_WIDTH = 800;
constexpr int CANVAS_HEIGHT = 500;

int main(int argc, char* argv[])
{
	shapes::Picture picture;
	gfx::PNGCanvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
	ShapeService shapeService = { std::cin, std::cout, picture, canvas };
	shapeService.Run();

	return EXIT_SUCCESS;
}