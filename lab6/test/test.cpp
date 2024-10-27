#include <gtest/gtest.h>
#include <sstream>
#include <vector>

#include "../src/graphics_lib.h"
#include "../src/modern_graphics_lib.h"
#include "../src/ModernGraphicsAdapter.h"
#include "../src/ModernGraphicsClassAdapter.h"

namespace mgl = modern_graphics_lib;
namespace gl = graphics_lib;

mgl::CRGBAColor ConvertToColor(const uint32_t colorValue)
{
	constexpr float colorScale = 1.0f / 255.0f;
	const auto red = static_cast<float>((colorValue >> 16) & 0xFF) * colorScale;
	const auto green = static_cast<float>((colorValue >> 8) & 0xFF) * colorScale;
	const auto blue = static_cast<float>(colorValue & 0xFF) * colorScale;
	const auto alpha = static_cast<float>((colorValue >> 24) & 0xFF) * colorScale;

	return {red, green, blue, alpha};
}

std::string DrawWithoutAdapter(const std::vector<mgl::CPoint> &points, const uint32_t color)
{
	std::stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);
	const auto rgbaColor = ConvertToColor(color);

	const auto first = points.begin();
	renderer.BeginDraw();

	for (auto it = first; it != points.end(); ++it)
	{
		if (it + 1 != points.end())
		{
			renderer.DrawLine(*it, *(it + 1), rgbaColor);
		}
		else
		{
			renderer.DrawLine(*it, *first, rgbaColor);
		}
	}

	renderer.EndDraw();

	return strm.str();
}

void DrawWithAdapter(mgl::CModernGraphicsRenderer &renderer, graphics_lib::ICanvas &adapter,
                     const std::vector<mgl::CPoint> &points, const uint32_t color)
{
	adapter.SetColor(color);
	renderer.BeginDraw();

	const auto first = points.begin();
	adapter.MoveTo(first->x, first->y);

	for (auto it = first + 1; it != points.end(); ++it)
	{
		adapter.LineTo(it->x, it->y);
	}

	adapter.LineTo(first->x, first->y);
	renderer.EndDraw();
}

std::string DrawWithObjectAdapter(const std::vector<mgl::CPoint> &points, const uint32_t color)
{
	std::stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);
	app::ModernGraphicsAdapter adapter(renderer);

	DrawWithAdapter(renderer, adapter, points, color);

	return strm.str();
}

std::string DrawShapeWithClassAdapter(const std::vector<mgl::CPoint> &points, const uint32_t color)
{
	std::stringstream strm;
	app::ModernGraphicsClassAdapter adapter(strm);

	DrawWithAdapter(adapter, adapter, points, color);

	return strm.str();
}

TEST(ObjectAdapterTest, InterfaceImplementation)
{
	std::stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);
	app::ModernGraphicsAdapter adapter(renderer);

	const auto canvas = dynamic_cast<graphics_lib::ICanvas *>(&adapter);
	ASSERT_NE(canvas, nullptr);
}

TEST(TriangleTest, DrawWithObjectAdapter)
{
	const auto triangle =
	{
		mgl::CPoint(10, 15),
		mgl::CPoint(100, 200),
		mgl::CPoint(150, 250),
	};

	constexpr uint32_t color = 0xFF5733FF;

	const auto originalShape = DrawWithoutAdapter(triangle, color);
	const auto withAdapterShape = DrawWithObjectAdapter(triangle, color);

	EXPECT_EQ(originalShape, withAdapterShape);
}

TEST(ClassAdapterTest, InterfaceImplementation)
{
	std::stringstream strm;
	app::ModernGraphicsClassAdapter adapter(strm);

	auto *canvas = dynamic_cast<graphics_lib::ICanvas *>(&adapter);
	ASSERT_NE(canvas, nullptr);

	auto *renderer = dynamic_cast<mgl::CModernGraphicsRenderer *>(&adapter);
	ASSERT_NE(renderer, nullptr);
}

TEST(TriangleTest, DrawWithClassAdapter)
{
	auto triangle =
	{
		mgl::CPoint(10, 15),
		mgl::CPoint(100, 200),
		mgl::CPoint(150, 250),
	};

	uint32_t color = 0xFF5733FF;

	const auto originalShape = DrawWithoutAdapter(triangle, color);
	const auto withAdapterShape = DrawShapeWithClassAdapter(triangle, color);

	EXPECT_EQ(originalShape, withAdapterShape);
}
