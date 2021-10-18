#include "Color.h"

using namespace std;

string GetColorHex(Color color) {
	switch (color)
	{
	case Color::Red:
		return "red";
	case Color::Green:
		return "green";
	case Color::Blue:
		return "blue";
	case Color::Pink:
		return "pink";
	case Color::Yellow:
		return "yellow";
	case Color::Black:
		return "black";
	default:
		throw std::invalid_argument("unknown color");
	}
}