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

	void MoveShape(const std::string& id, double dx, double dy) const;

	void MovePicture(double dx, double dy) const;

	void DeleteShape(const std::string& id);

	void List(const std::function<void(const std::string&)>& callback);

	void ChangeColor(const std::string& id, Color color) const;

	void ChangeShape(const std::string& id, std::unique_ptr<IDrawingStrategy>&& strategy) const;

	void DrawShape(const std::string& id, gfx::ICanvas& canvas) const;

	void DrawPicture(gfx::ICanvas& canvas);

private:
	std::map<std::string, std::unique_ptr<Shape>> m_shapes = {};
};
}
#endif //PICTURE_H