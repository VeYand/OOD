#ifndef SHAPESERVICE_H
#define SHAPESERVICE_H

#include "ShapeType.h"
#include "../gfx/ICanvas.h"
#include "../shapes/Picture.h"
#include <functional>
#include <unordered_map>
#include <string>
#include <memory>
#include <sstream>

class ShapeService
{
public:
	ShapeService(std::istream& in, std::ostream& out, shapes::Picture& picture, gfx::ICanvas& canvas);

	void Run();

private:
	std::istream& m_in;
	std::ostream& m_out;
	shapes::Picture& m_picture;
	gfx::ICanvas& m_canvas;

	using CommandHandler = std::function<void(std::istringstream&)>;
	std::unordered_map<std::string, CommandHandler> m_commands;

	void RegisterCommands();

	void AddShape(std::istringstream& iss);
	void MoveShape(std::istringstream& iss) const;
	void DeleteShape(std::istringstream& iss) const;
	void ListShape() const;
	void ChangeColor(std::istringstream& iss) const;
	void MovePicture(std::istringstream& iss) const;
	void ChangeShape(std::istringstream& iss);
	void DrawShape(std::istringstream& iss);
	void DrawPicture() const;
	std::unique_ptr<shapes::IFigureStrategy> CreateDrawStrategyFromStream(std::istringstream& iss, const std::string& type);

	static std::string ConvertShapeTypeToString(ShapeType type);
	static ShapeType ConvertStringToShapeType(const std::string& typeStr);
	static bool ParseColor(std::string colorStr, shapes::Color& color);

};

#endif // SHAPESERVICE_H
