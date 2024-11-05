#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H

#include <memory>
#include <sstream>

#include "IShapeFactory.h"
#include "../Shape/CRectangle.h"
#include "../Shape/CEllipse.h"
#include "../Shape/CTriangle.h"
#include "ShapeType.h"

class ShapeFactory final : public IShapeFactory
{
public:
	std::unique_ptr<CShape> CreateShape(const std::string &description) override
	{
		std::istringstream iss(description);
		std::string colorStr, type;
		RGBAColor color;

		iss >> colorStr >> type;
		if (colorStr.empty() || type.empty())
		{
			throw std::invalid_argument("Insufficient arguments for shape");
		}

		if (!ParseColor(colorStr, color))
		{
			throw std::invalid_argument("Invalid color format");
		}

		if (type == ShapeTypeToString(ShapeType::TRIANGLE))
		{
			return CreateTriangle(color, iss);
		}
		if (type == ShapeTypeToString(ShapeType::ELLIPSE))
		{
			return CreateEllipse(color, iss);
		}
		if (type == ShapeTypeToString(ShapeType::RECTANGLE))
		{
			return CreateRectangle(color, iss);
		}

		throw std::invalid_argument("Unknown shape");
	}

private:
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

	static std::unique_ptr<CTriangle> CreateTriangle(RGBAColor color, std::istringstream &iss)
	{
		double x1, y1, x2, y2, x3, y3;
		if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3))
		{
			throw std::invalid_argument("Invalid parameters for triangle");
		}

		return ...;
	}

	static std::unique_ptr<CEllipse> CreateEllipse(RGBAColor color, std::istringstream &iss)
	{
		double centerX, centerY, horizontalRadius, verticalRadius;
		if (!(iss >> centerX >> centerY >> horizontalRadius >> verticalRadius))
		{
			throw std::invalid_argument("Invalid parameters for circle");
		}
		if (horizontalRadius < 0 || verticalRadius < 0)
		{
			throw std::invalid_argument("Radius must be non-negative for circle");
		}

		return ...;
	}

	static std::unique_ptr<CRectangle> CreateRectangle(RGBAColor color, std::istringstream &iss)
	{
		double leftTopX, leftTopY, width, height;
		if (!(iss >> leftTopX >> leftTopY >> width >> height))
		{
			throw std::invalid_argument("Invalid parameters for rectangle");
		}
		if (width < 0 || height < 0)
		{
			throw std::invalid_argument("Width and height must be non-negative for rectangle");
		}

		return ...;
	}
};

#endif //SHAPEFACTORY_H
