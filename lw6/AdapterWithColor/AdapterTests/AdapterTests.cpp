#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Adapter'/ModernGraphicsLibAdapter.h"
#include "../Adapter'/ShapeDrawindLib.h"
#include <iostream>
#include <sstream>


using namespace std;


void DrawLine(ostream& out, modern_graphics_lib::CPoint from, modern_graphics_lib::CPoint to, const uint32_t color = 0x000000)
{
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsLibAdapter libAdapter(renderer);
	libAdapter.SetColor(color);
	libAdapter.MoveTo(from.x, from.y);
	libAdapter.LineTo(to.x, to.y);
}

SCENARIO("adapter tests")
{ 
	WHEN("color by default")
	{
		ostringstream strOut;

		DrawLine(strOut, modern_graphics_lib::CPoint(1, 1), modern_graphics_lib::CPoint(5, 5));

		string result = "<draw>\n"
			"  <line fromX='1' fromY='1' toX='5' toY='5'>\n"
			"    <color r='0' g='0' b='0' a='1'/>\n"
			"  </line>\n"
			"</draw>\n";

		REQUIRE(result == strOut.str());
	}
	WHEN("with color")
	{
		ostringstream strOut;

		DrawLine(strOut, modern_graphics_lib::CPoint(1, 1), modern_graphics_lib::CPoint(5, 5), 0xfa12ab);

		string result = "<draw>\n"
			"  <line fromX='1' fromY='1' toX='5' toY='5'>\n"
			"    <color r='0.980392' g='0.0705882' b='0.670588' a='1'/>\n"
			"  </line>\n"
			"</draw>\n";

		REQUIRE(result == strOut.str());
	}
}
