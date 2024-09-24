#include "Picture.h"

#include "exception/ShapeAlreadyExistsException.h"
#include "exception/ShapeNotFoundException.h"

#include <iomanip>
#include <iostream>

void shapes::Picture::AddShape(const std::string& id, std::unique_ptr<Shape>&& shape)
{
	if (m_shapes.contains(id))
	{
		throw ShapeAlreadyExistsException();
	}
	m_shapes.emplace(id, std::move(shape));
}

void shapes::Picture::MoveShape(const std::string& id, const double dx, const double dy) const
{
	if (!m_shapes.contains(id))
	{
		throw ShapeNotFoundException();
	}

	const auto& shape = m_shapes.at(id);
	shape->Move(dx, dy);
}

void shapes::Picture::DeleteShape(const std::string& id)
{
	if (!m_shapes.contains(id))
	{
		throw ShapeNotFoundException();
	}

	m_shapes.erase(id);
}

void shapes::Picture::List(const std::function<void(const std::string&)>& callback)
{
	int count = 1;
	for (const auto& [id, shape] : m_shapes)
	{
		std::ostringstream oss;
		oss << count << " "
			<< shape->GetName() << " "
			<< id << " "
			<< "#" << std::hex << std::setw(6) << std::setfill('0') << shape->GetColor()
			<< std::defaultfloat
			<< " " << shape->ToStringStrategy();

		callback(oss.str());
		count++;
	}
}

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

void shapes::Picture::ChangeShape(const std::string& id, std::unique_ptr<IDrawingStrategy>&& strategy) const
{
	if (!m_shapes.contains(id))
	{
		throw ShapeNotFoundException();
	}

	m_shapes.at(id)->SetDrawingStrategy(std::move(strategy));
}

void shapes::Picture::DrawShape(const std::string& id, gfx::ICanvas& canvas) const
{
	if (!m_shapes.contains(id))
	{
		throw ShapeNotFoundException();
	}

	m_shapes.at(id)->Draw(canvas);
}

void shapes::Picture::DrawPicture(gfx::ICanvas& canvas)
{
	for (const auto& [id, shape] : m_shapes)
	{
		shape->Draw(canvas);
	}
}