#include "ShapeService.h"
#include "../shapes/strategy/CircleFigureStrategy.h"
#include "../shapes/strategy/LineFigureStrategy.h"
#include "../shapes/strategy/RectangleFigureStrategy.h"
#include "../shapes/strategy/TextFigureStrategy.h"
#include "../shapes/strategy/TriangleFigureStrategy.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>

ShapeService::ShapeService(std::istream& in, std::ostream& out, shapes::Picture& picture, gfx::ICanvas& canvas)
	: m_in(in), m_out(out), m_picture(picture), m_canvas(canvas)
{
	RegisterCommands();
}

void ShapeService::RegisterCommands()
{
	m_commands["AddShape"] = [this](std::istringstream& iss) { AddShape(iss); };
	m_commands["MoveShape"] = [this](std::istringstream& iss) { MoveShape(iss); };
	m_commands["DeleteShape"] = [this](std::istringstream& iss) { DeleteShape(iss); };
	m_commands["List"] = [this](std::istringstream&) { ListShape(); };
	m_commands["ChangeColor"] = [this](std::istringstream& iss) { ChangeColor(iss); };
	m_commands["MovePicture"] = [this](std::istringstream& iss) { MovePicture(iss); };
	m_commands["ChangeShape"] = [this](std::istringstream& iss) { ChangeShape(iss); };
	m_commands["DrawShape"] = [this](std::istringstream& iss) { DrawShape(iss); };
	m_commands["DrawPicture"] = [this](std::istringstream&) { DrawPicture(); };
}

void ShapeService::Run()
{
	std::string line;
	while (std::getline(m_in, line))
	{
		std::istringstream iss(line);
		std::string commandName;
		iss >> commandName;

		if (commandName.empty())
			continue;

		if (commandName == "...")
		{
			break;
		}

		auto it = m_commands.find(commandName);
		if (it != m_commands.end())
		{
			try
			{
				it->second(iss);
			}
			catch (const std::exception& e)
			{
				m_out << e.what() << std::endl;
			}
		}
		else
		{
			m_out << "Unknown command: " << commandName << std::endl;
		}
	}
}

void ShapeService::AddShape(std::istringstream& iss)
{
	std::string id, colorStr, type;
	shapes::Color color;

	iss >> id >> colorStr >> type;
	if (id.empty() || colorStr.empty() || type.empty())
	{
		throw std::invalid_argument("Insufficient arguments for AddShape command");
	}

	if (!ParseColor(colorStr, color))
	{
		throw std::invalid_argument("Invalid color format");
	}

	auto strategy = CreateDrawStrategyFromStream(iss, type);
	if (strategy)
	{
		auto shape = std::make_unique<shapes::Shape>(color, std::move(strategy));
		m_picture.AddShape(id, std::move(shape));
	}
	else
	{
		m_out << "Invalid shape type " << type << std::endl;
	}
}

std::unique_ptr<shapes::IFigureStrategy> ShapeService::CreateDrawStrategyFromStream(std::istringstream& iss, const std::string& type)
{
	if (type == ConvertShapeTypeToString(ShapeType::RECTANGLE))
	{
		double leftTopX, leftTopY, width, height;
		if (!(iss >> leftTopX >> leftTopY >> width >> height))
		{
			m_out << "Invalid parameters for rectangle" << std::endl;
			return nullptr;
		}
		if (width < 0 || height < 0)
		{
			m_out << "Width and height must be non-negative for rectangle" << std::endl;
			return nullptr;
		}

		return std::move(std::make_unique<shapes::RectangleFigureStrategy>(
			shapes::Rect(shapes::Point(leftTopX, leftTopY), shapes::Point(leftTopX + width, leftTopY + height))
			));
	}

	if (type == ConvertShapeTypeToString(ShapeType::CIRCLE))
	{
		double centerX, centerY, radius;
		if (!(iss >> centerX >> centerY >> radius))
		{
			m_out << "Invalid parameters for circle" << std::endl;
			return nullptr;
		}
		if (radius < 0)
		{
			m_out << "Radius must be non-negative for circle" << std::endl;
			return nullptr;
		}

		return std::move(std::make_unique<shapes::CircleFigureStrategy>(shapes::Point(centerX, centerY), radius));
	}

	if (type == ConvertShapeTypeToString(ShapeType::TRIANGLE))
	{
		double x1, y1, x2, y2, x3, y3;
		if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3))
		{
			m_out << "Invalid parameters for triangle" << std::endl;
			return nullptr;
		}

		return std::move(std::make_unique<shapes::TriangleFigureStrategy>(
			shapes::Point(x1, y1), shapes::Point(x2, y2), shapes::Point(x3, y3)
			));
	}

	if (type == ConvertShapeTypeToString(ShapeType::LINE))
	{
		double x1, y1, x2, y2;
		if (!(iss >> x1 >> y1 >> x2 >> y2))
		{
			m_out << "Invalid parameters for line" << std::endl;
			return nullptr;
		}

		return std::move(std::make_unique<shapes::LineFigureStrategy>(
			shapes::Point(x1, y1), shapes::Point(x2, y2)
			));
	}

	if (type == ConvertShapeTypeToString(ShapeType::TEXT))
	{
		double leftTopX, leftTopY, fontSize;
		std::string text;
		if (!(iss >> leftTopX >> leftTopY >> fontSize))
		{
			m_out << "Invalid parameters for text" << std::endl;
			return nullptr;
		}
		if (fontSize < 0)
		{
			m_out << "Font size must be non-negative for text" << std::endl;
			return nullptr;
		}
		std::getline(iss, text);
		if (!text.empty() && text[0] == ' ')
		{
			text.erase(0, 1);
		}

		return std::move(std::make_unique<shapes::TextFigureStrategy>(
			shapes::Point(leftTopX, leftTopY), fontSize, text
			));
	}

	return nullptr;
}

bool ShapeService::ParseColor(std::string colorStr, shapes::Color& color)
{
	if (colorStr.size() != 7 || colorStr[0] != '#')
	{
		return false;
	}
	std::stringstream ss;
	ss << std::hex << colorStr.append("FF").substr(1);

	if (!(ss >> color))
	{
		return false;
	}

	return ss.eof();
}

void ShapeService::MoveShape(std::istringstream& iss) const
{
	std::string id;
	double dx, dy;

	if (!(iss >> id >> dx >> dy))
	{
		m_out << "Invalid arguments for MoveShape" << std::endl;
		return;
	}

	m_picture.GetShape(id)->Move(dx, dy);
}

void ShapeService::DeleteShape(std::istringstream& iss) const
{
	std::string id;
	if (!(iss >> id))
	{
		m_out << "Invalid arguments for DeleteShape" << std::endl;
		return;
	}

	m_picture.DeleteShape(id);
}

void ShapeService::ListShape() const
{
	auto shapes = m_picture.ListShapes();

	int count = 1;
	for (const auto& [id, shape] : shapes)
	{
		m_out << std::dec << count << " "
			<< shape->GetName() << " "
			<< id << " "
			<< "#" << std::hex << std::setw(6) << std::setfill('0') << shape->GetColor()
			<< std::defaultfloat
			<< " " << shape->ToStringStrategy() << std::endl;;

		count++;
	}
}

void ShapeService::ChangeColor(std::istringstream& iss) const
{
	std::string id, colorStr;
	shapes::Color color;

	if (!(iss >> id >> colorStr))
	{
		m_out << "Invalid arguments for ChangeColor" << std::endl;
		return;
	}

	if (!ParseColor(colorStr, color))
	{
		m_out << "Invalid color format. Expected HEX" << std::endl;
		return;
	}

	m_picture.ChangeColor(id, color);
}

void ShapeService::MovePicture(std::istringstream& iss) const
{
	double dx, dy;
	if (!(iss >> dx >> dy))
	{
		m_out << "Invalid arguments for MovePicture" << std::endl;
		return;
	}

	m_picture.MovePicture(dx, dy);
}

void ShapeService::ChangeShape(std::istringstream& iss)
{
	std::string id, type;

	iss >> id  >> type;
	if (id.empty() || type.empty())
	{
		throw std::invalid_argument("Insufficient arguments for AddShape command");
	}

	auto strategy = CreateDrawStrategyFromStream(iss, type);
	if (strategy)
	{
		m_picture.GetShape(id)->SetDrawingStrategy(std::move(strategy));
	}
	else
	{
		m_out << "Invalid shape type " << type << std::endl;
	}
}

void ShapeService::DrawShape(std::istringstream& iss)
{
	std::string id;
	if (!(iss >> id))
	{
		m_out << "Invalid arguments for DrawShape" << std::endl;
		return;
	}

	m_picture.GetShape(id)->Draw(m_canvas);
}

void ShapeService::DrawPicture() const
{
	m_picture.DrawPicture(m_canvas);
}

std::string ShapeService::ConvertShapeTypeToString(const ShapeType type)
{
	switch (type)
	{
	case ShapeType::RECTANGLE:
		return "rectangle";
	case ShapeType::CIRCLE:
		return "circle";
	case ShapeType::TRIANGLE:
		return "triangle";
	case ShapeType::LINE:
		return "line";
	case ShapeType::TEXT:
		return "text";
	default:
		return "";
	}
}

ShapeType ShapeService::ConvertStringToShapeType(const std::string& typeStr)
{
	if (typeStr == "rectangle")
		return ShapeType::RECTANGLE;
	if (typeStr == "circle")
		return ShapeType::CIRCLE;
	if (typeStr == "triangle")
		return ShapeType::TRIANGLE;
	if (typeStr == "line")
		return ShapeType::LINE;
	if (typeStr == "text")
		return ShapeType::TEXT;
	throw std::invalid_argument("Unknown shape type: " + typeStr);
}