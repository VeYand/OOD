#ifndef PNGCANVAS_H
#define PNGCANVAS_H
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include "ICanvas.h"
#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace gfx
{
class PNGCanvas final : public ICanvas
{
public:
	using Color = uint32_t;

	struct ColorStruct
	{
		uint8_t r, g, b, a;
	};

	struct Point
	{
		double x;
		double y;
	};

	PNGCanvas(const unsigned width, const unsigned height)
		: m_width(width), m_height(height)
	{
		m_pixels.resize(width * height * 4, 255);
	}

	~PNGCanvas() override
	{
		SaveToFile("output.png");
	}

	void SetColor(const Color color) override
	{
		ColorStruct result{};

		result.r = static_cast<uint8_t>((color >> 24) & 0xFF);
		result.g = static_cast<uint8_t>((color >> 16) & 0xFF);
		result.b = static_cast<uint8_t>((color >> 8) & 0xFF);
		result.a = static_cast<uint8_t>(color & 0xFF);

		m_color = result;
	}

	void MoveTo(const double x, const double y) override
	{
		m_currentPosition = { x, y };
	}

	void LineTo(const double x, const double y) override
	{
		DrawLine(m_currentPosition.x, m_currentPosition.y, x, y);
		m_currentPosition = { x, y };
	}

	void DrawEllipse(const double cx, const double cy, const double rx, const double ry) override
	{
		constexpr int segments = 100;
		constexpr double angleStep = 2 * M_PI / segments;

		double prevX = cx + rx;
		double prevY = cy;

		for (int i = 1; i <= segments; ++i)
		{
			const double angle = i * angleStep;
			const double newX = cx + rx * cos(angle);
			const double newY = cy + ry * sin(angle);
			DrawLine(prevX, prevY, newX, newY);
			prevX = newX;
			prevY = newY;
		}
	}

	void DrawText(double left, double top, double fontSize, const std::string& text) override
	{
		std::ifstream fontFile(FONT_PATH, std::ios::binary);
		if (!fontFile.is_open())
		{
			std::cerr << "Failed to open font file!" << std::endl;
			return;
		}

		std::vector<unsigned char> fontBuffer((std::istreambuf_iterator<char>(fontFile)),
			std::istreambuf_iterator<char>());
		fontFile.close();

		stbtt_fontinfo font;
		if (!stbtt_InitFont(&font, fontBuffer.data(), stbtt_GetFontOffsetForIndex(fontBuffer.data(), 0)))
		{
			std::cerr << "Failed to load font!" << std::endl;
			return;
		}
		float scale = stbtt_ScaleForPixelHeight(&font, static_cast<float>(fontSize));
		auto x = static_cast<float>(left);
		auto y = static_cast<float>(top);
		int ascent, descent, lineGap;
		stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
		ascent *= scale;
		descent *= scale;

		for (const char* p = text.c_str(); *p; ++p)
		{
			int ch = *p;

			int advance, lsb;
			stbtt_GetCodepointHMetrics(&font, ch, &advance, &lsb);

			int c_x1, c_y1, c_x2, c_y2;
			stbtt_GetCodepointBitmapBox(&font, ch, scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

			int bitmapWidth = c_x2 - c_x1;
			int bitmapHeight = c_y2 - c_y1;

			std::vector<unsigned char> charBitmap(bitmapWidth * bitmapHeight);

			stbtt_MakeCodepointBitmap(&font, charBitmap.data(), bitmapWidth, bitmapHeight, bitmapWidth, scale, scale, ch);

			for (int cy = 0; cy < bitmapHeight; ++cy)
			{
				for (int cx = 0; cx < bitmapWidth; ++cx)
				{
					int srcIndex = cy * bitmapWidth + cx;
					unsigned char alpha = charBitmap[srcIndex];
					if (alpha > 0)
					{
						PutPixel(static_cast<int>(x) + cx + c_x1, static_cast<int>(y) + cy + ascent + c_y1);
					}
				}
			}
			x += advance * scale;
		}
	}

	void SaveToFile(const std::string& filename)
	{
		stbi_write_png(filename.c_str(), m_width, m_height, 4, m_pixels.data(), m_width * 4);
	};

private:
	unsigned m_width;
	unsigned m_height;
	ColorStruct m_color{};
	Point m_currentPosition = { 0, 0 };
	std::vector<uint8_t> m_pixels;
	const char* FONT_PATH = "/home/veyand/Projects/OOD/lab1/1_4/lib/gfx/font/Minecraft-Regular.ttf";

	void PutPixel(int x, int y)
	{
		if (x >= 0 && x < m_width && y >= 0 && y < m_height)
		{
			int index = 4 * (y * m_width + x);
			m_pixels[index] = m_color.r;
			m_pixels[index + 1] = m_color.g;
			m_pixels[index + 2] = m_color.b;
			m_pixels[index + 3] = m_color.a;
		}
	}

	void DrawLine(double x1, double y1, double x2, double y2)
	{
		int ix1 = static_cast<int>(std::round(x1));
		int iy1 = static_cast<int>(std::round(y1));
		int ix2 = static_cast<int>(std::round(x2));
		int iy2 = static_cast<int>(std::round(y2));

		int dx = std::abs(ix2 - ix1), dy = std::abs(iy2 - iy1);
		int sx = (ix1 < ix2) ? 1 : -1;
		int sy = (iy1 < iy2) ? 1 : -1;
		int err = dx - dy;

		while (true)
		{
			PutPixel(ix1, iy1);
			if (ix1 == ix2 && iy1 == iy2)
				break;
			int e2 = 2 * err;
			if (e2 > -dy)
			{
				err -= dy;
				ix1 += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				iy1 += sy;
			}
		}
	}
};

} // namespace gfx

#endif // PNGCANVAS_H