#ifndef GEOM_H
#define GEOM_H

struct Point
{
	int x = 0;
	int y = 0;
};

struct Size
{
	int width = 0;
	int height = 0;
};

// Точка передаётся в локальных координатах.
inline bool IsPointInSize(const Point p, const Size size) noexcept
{
	return p.x >= 0 && p.y >= 0 && p.x < size.width && p.y < size.height;
}

#endif //GEOM_H
