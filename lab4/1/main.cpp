#include "Client.h"
#include "Canvas/PNGCanvas/PNGCanvas.h"
#include "Designer/Designer.h"
#include "Painter/Painter.h"
#include "ShapeFactory/ShapeFactory.h"

using namespace std;

constexpr int CANVAS_WIDTH = 800;
constexpr int CANVAS_HEIGHT = 500;

int main()
{
	gfx::PNGCanvas canvas(CANVAS_WIDTH, CANVAS_HEIGHT);
	ShapeFactory shapeFactory;
	Designer designer(shapeFactory);
	Painter painter;
	const Client client(designer);
	client.HandleCommand(std::cin, canvas, painter);
	canvas.SaveToFile('output.txt');

	return EXIT_SUCCESS;
}
