#ifndef COMMONTYPES_H
#define COMMONTYPES_H
#include <cstdint>

template<typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
};

typedef Rect<double> RectD;
typedef uint32_t RGBAColor;

#endif //COMMONTYPES_H
