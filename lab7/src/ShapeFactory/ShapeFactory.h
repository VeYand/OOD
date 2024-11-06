#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <memory>
#include <sstream>

#include "IShapeFactory.h"
#include "../Shape/CRectangle.h"
#include "../Shape/CEllipse.h"
#include "../Shape/CTriangle.h"
#include "ShapeType.h"
#include "../Shape/Style/CStyle.h"

class ShapeFactory final : public IShapeFactory
{
public:
	std::unique_ptr<IShape> CreateShape(const std::string &description) override
	{
		std::istringstream iss(description);
		std::string type;

		iss >> type;
		if (type.empty())
		{
			throw std::invalid_argument("Insufficient arguments for shape");
		}

		if (type == ShapeTypeToString(ShapeType::TRIANGLE))
		{
			return CreateTriangle(iss);
		}
		if (type == ShapeTypeToString(ShapeType::ELLIPSE))
		{
			return CreateEllipse(iss);
		}
		if (type == ShapeTypeToString(ShapeType::RECTANGLE))
		{
			return CreateRectangle(iss);
		}

		throw std::invalid_argument("Unknown shape");
	}

private:
	static std::unique_ptr<CTriangle> CreateTriangle(std::istringstream &iss)
	{
		const auto rect = ParseShapeRect(iss);
		const auto outlineStyle = ParseStyle(iss);
		const auto fillStyle = ParseStyle(iss);

		return std::make_unique<CTriangle>(rect, outlineStyle, fillStyle);
	}

	static std::unique_ptr<CEllipse> CreateEllipse(std::istringstream &iss)
	{
		const auto rect = ParseShapeRect(iss);
		const auto outlineStyle = ParseStyle(iss);
		const auto fillStyle = ParseStyle(iss);

		return std::make_unique<CEllipse>(rect, outlineStyle, fillStyle);
	}

	static std::unique_ptr<CRectangle> CreateRectangle(std::istringstream &iss)
	{
		const auto rect = ParseShapeRect(iss);
		const auto outlineStyle = ParseStyle(iss);
		const auto fillStyle = ParseStyle(iss);

		return std::make_unique<CRectangle>(rect, outlineStyle, fillStyle);
	}

	static RectD ParseShapeRect(std::istringstream &iss)
	{
		double left, top, width, height;

		if (!(iss >> left >> top >> width >> height))
		{
			throw std::invalid_argument("Invalid rect parameters");
		}

		if (width < 0 || height < 0)
		{
			throw std::invalid_argument("Width and height must be non-negative");
		}

		return {left, top, width, height};
	}

	static std::unique_ptr<IStyle> ParseStyle(std::istringstream &iss)
	{
		std::string colorStr;
		RGBAColor color;

		if (!(iss >> colorStr) || !ParseColor(colorStr, color))
		{
			return std::make_unique<CStyle>();
		}

		auto style = std::make_unique<CStyle>();
		style->SetColor(color);
		style->SetIsEnabled(true);

		return style;
	}


	static bool ParseColor(std::string colorStr, RGBAColor &color)
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
};

#endif //SHAPEFACTORY_H
