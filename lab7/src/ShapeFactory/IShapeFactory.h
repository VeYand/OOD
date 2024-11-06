#ifndef ISHAPEFACTORY_H
#define ISHAPEFACTORY_H

#include <memory>
#include <string>

#include "../Shape/CShape.h"

class IShapeFactory
{
public:
	virtual std::unique_ptr<IShape> CreateShape(const std::string &description) = 0;

	virtual ~IShapeFactory() = default;
};

#endif //ISHAPEFACTORY_H
