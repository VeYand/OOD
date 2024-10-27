#ifndef MODERNGRAPHICSCLASSADAPTER_H
#define MODERNGRAPHICSCLASSADAPTER_H

#include "graphics_lib.h"
#include "modern_graphics_lib.h"

namespace app
{
	class ModernGraphicsClassAdapter : public graphics_lib::ICanvas, public modern_graphics_lib::CModernGraphicsRenderer
	{
	public:
		explicit ModernGraphicsClassAdapter(std::ostream &strm)
			: CModernGraphicsRenderer(strm),
			  m_start(0, 0)
		{
		}

		void SetColor(const uint32_t color) override
		{
			m_color = color;
		}

		void MoveTo(const int x, const int y) override
		{
			m_start = {x, y};
		}

		void LineTo(const int x, const int y) override
		{
			const modern_graphics_lib::CPoint end(x, y);

			DrawLine(m_start, end, m_color);

			m_start.x = end.x;
			m_start.y = end.y;
		}

	private:
		uint32_t m_color{};
		modern_graphics_lib::CPoint m_start;
	};
}

#endif //MODERNGRAPHICSCLASSADAPTER_H
