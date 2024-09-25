#ifndef PICTURE_H
#define PICTURE_H
#include "Shape.h"

#include <functional>
#include <map>
#include <memory>

namespace shapes
{
class Picture
{
public:
	void AddShape(const std::string& id, std::unique_ptr<Shape>&& shape);

	void MovePicture(double dx, double dy) const;

	void DeleteShape(const std::string& id);

	void ChangeColor(const std::string& id, Color color) const;

	void DrawPicture(gfx::ICanvas& canvas);

	[[nodiscard]] Shape* GetShape(const std::string& id) const;

	[[nodiscard]] std::vector<std::pair<std::string, Shape*> > ListShapes() const;

private:
	std::map<std::string, std::unique_ptr<Shape> > m_shapes = {};
	std::vector<std::string> m_shapeIds = {};
};
}
#endif //PICTURE_H