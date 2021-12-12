#pragma once
#include <iostream>

struct Point
{
	double x;
	double y;
};

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
};

typedef Rect<double> RectD;
typedef std::uint32_t RGBAColor;