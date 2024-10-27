#ifndef MODERN_GRAPHICS_LIB_H
#define MODERN_GRAPHICS_LIB_H

#include <iostream>
#include <format>

// Пространство имен современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib
{
	class CPoint
	{
	public:
		CPoint(const int x, const int y) : x(x), y(y)
		{
		}

		int x;
		int y;
	};

	// Класс для современного рисования графики
	class CModernGraphicsRenderer
	{
	public:
		explicit CModernGraphicsRenderer(std::ostream &strm) : m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			if (m_drawing) // Завершаем рисование, если оно было начато
			{
				EndDraw();
			}
		}

		// Этот метод должен быть вызван в начале рисования
		void BeginDraw()
		{
			if (m_drawing)
			{
				throw std::logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << std::endl;
			m_drawing = true;
		}

		// Выполняет рисование линии
		void DrawLine(const CPoint &start, const CPoint &end, const uint32_t &color)
		{
			if (!m_drawing)
			{
				throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
			}

			const auto [red, green, blue, alpha] = ConvertToColor(color);

			m_out << std::format(R"(  <line fromX="{}" fromY="{}" toX="{}" toY="{}">)", start.x, start.y, end.x,
			                     end.y) << std::endl;
			m_out << std::format(
				R"(    <color r="{}" g="{}" b="{}" a="{}" />)",
				red,
				green,
				blue,
				alpha
			) << std::endl;
			m_out << R"(  </line>)" << std::endl;
		}

		// Этот метод должен быть вызван в конце рисования
		void EndDraw()
		{
			if (!m_drawing)
			{
				throw std::logic_error("Drawing has not been started");
			}
			m_out << "</draw>" << std::endl;
			m_drawing = false;
		}

	private:
		std::ostream &m_out;
		bool m_drawing = false;

		struct Color
		{
			float red, green, blue, alpha;
		};

		static Color ConvertToColor(const uint32_t colorValue)
		{
			constexpr float colorScale = 1.0f / 255.0f;
			const auto red = static_cast<float>((colorValue >> 16) & 0xFF) * colorScale;
			const auto green = static_cast<float>((colorValue >> 8) & 0xFF) * colorScale;
			const auto blue = static_cast<float>(colorValue & 0xFF) * colorScale;
			const auto alpha = static_cast<float>((colorValue >> 24) & 0xFF) * colorScale;

			return {red, green, blue, alpha};
		}
	};
}

#endif //MODERN_GRAPHICS_LIB_H
