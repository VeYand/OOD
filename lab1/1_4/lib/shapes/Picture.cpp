#include "Picture.h"

#include "exception/ShapeAlreadyExistsException.h"
#include "exception/ShapeNotFoundException.h"

#include <iomanip>

void shapes::Picture::AddShape(const std::string& id, std::unique_ptr<Shape>&& shape)
{
	if (m_shapes.contains(id))
	{
		throw ShapeAlreadyExistsException();
	}
	m_shapes.emplace(id, std::move(shape));
	// TODO Метод не безопасен к возникновению исключения
	m_shapeIds.emplace_back(id);
}

void shapes::Picture::DeleteShape(const std::string& id)
{
	if (!m_shapes.contains(id))
	{
		throw ShapeNotFoundException();
	}

	m_shapes.erase(id);
	auto it = std::remove(m_shapeIds.begin(), m_shapeIds.end(), id);
	// TODO Подумать над этим условием
	if (it != m_shapeIds.end())
	{
		m_shapeIds.erase(it, m_shapeIds.end());
	}
}

// TODO Убрать ChangeColor
void shapes::Picture::ChangeColor(const std::string& id, const Color color) const
{
	if (!m_shapes.contains(id))
	{
		throw ShapeNotFoundException();
	}

	const auto& shape = m_shapes.at(id);
	shape->SetColor(color);
}

void shapes::Picture::MovePicture(double dx, double dy) const
{
	for (const auto& pair : m_shapes)
	{
		pair.second->Move(dx, dy);
	}
}

void shapes::Picture::DrawPicture(gfx::ICanvas& canvas)
{
	for (const auto& id : m_shapeIds)
	{
		GetShape(id)->Draw(canvas); // TODO Сделать o(n)
	}
}

shapes::Shape* shapes::Picture::GetShape(const std::string& id) const
{
	if (!m_shapes.contains(id))
	{
		throw ShapeNotFoundException();
	}

	return m_shapes.at(id).get();
}

[[nodiscard]] std::vector<std::pair<std::string, shapes::Shape*> > shapes::Picture::ListShapes() const
{
	std::vector<std::pair<std::string, Shape*> > shapeList;
	shapeList.reserve(m_shapeIds.size());

	for (const auto& id : m_shapeIds)
	{
		shapeList.emplace_back(id, GetShape(id));
	}

	return shapeList;
}