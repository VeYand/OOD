#ifndef MODERNGRAPHICSADAPTER_H
#define MODERNGRAPHICSADAPTER_H

#include "graphics_lib.h"
#include "modern_graphics_lib.h"

namespace app
{
	class ModernGraphicsAdapter : public graphics_lib::ICanvas
	{
	public:
		explicit ModernGraphicsAdapter(
			modern_graphics_lib::CModernGraphicsRenderer &modernRenderer): m_start(0, 0),
			                                                               m_renderer(modernRenderer)
		{
		}

		void SetColor(const uint32_t color) override
		{
			m_color = color;
		}

		void MoveTo(int x, int y) override
		{
			m_start = {x, y};
		}

		void LineTo(const int x, const int y) override
		{
			const modern_graphics_lib::CPoint end(x, y);

			m_renderer.DrawLine(m_start, end, m_color);

			m_start = end;
		}

	private:
		uint32_t m_color{};
		modern_graphics_lib::CPoint m_start;
		modern_graphics_lib::CModernGraphicsRenderer &m_renderer;
	};
}


#endif //MODERNGRAPHICSADAPTER_H