#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Adapter'/ModernGraphicsLibAdapter.h"
#include "../Adapter'/ShapeDrawindLib.h"
#include <iostream>
#include <sstream>


using namespace std;


void DrawLine(ostream& out, modern_graphics_lib::CPoint from, modern_graphics_lib::CPoint to)
{
	modern_graphics_lib::CModernGraphicsRenderer renderer(out);
	ModernGraphicsLibAdapter libAdapter(renderer);
	libAdapter.MoveTo(from.x, from.y);
	libAdapter.LineTo(to.x, to.y);
}

SCENARIO("adapter tests")
{ 
	ostringstream strOut;

	DrawLine(strOut, modern_graphics_lib::CPoint(1, 1), modern_graphics_lib::CPoint(5, 5));
	
	string result = "<draw>\n"
		"  <line fromX='1' fromY='1' toX='5' toY='5'/>\n"
		"</draw>\n";

	REQUIRE(result == strOut.str());
}
