#pragma once
#include <stdexcept>

enum class Color {
	Red,
	Green,
	Blue,
	Pink,
	Yellow,
	Black,
};

std::string GetColorHex(Color color);