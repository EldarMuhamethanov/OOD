#include "CCanvas.h"

using namespace std;

const int CANVAS_WIDTH = 1000;
const int CANVAS_HEIGHT = 1000;


CCanvas::CCanvas(ostream& out)
	: m_output(out)
{
	m_output << "<svg "
		<< "xmlns='http://www.w3.org/2000/svg' "
		<< "width='" << CANVAS_WIDTH << "' height='"<< CANVAS_HEIGHT << "' "
		<< "viewPort='0 0 " << CANVAS_WIDTH << " " << CANVAS_HEIGHT << "'>" 
		<< endl;
}

CCanvas::~CCanvas()
{
	m_output << "</svg>" << endl;
}

void CCanvas::SetColor(Color color)
{
	m_color = color;
}

void CCanvas::DrawLine(Point from, Point to)
{
	m_output 
		<< "<line "
		<< "x1 = '" << from.x << "' y1 = '" << from.y
		<< "' x2 = '" << to.x << "' y2 = '" << to.y << "' "
		<< "stroke = '" << GetColorHex(m_color) << "' stroke-width = '5'/>"
		<< endl;
}

void CCanvas::DrawEllipse(Point center, double verticalRadius, double horizontalRadius)
{
	m_output
		<< "<ellipse "
		<< "rx = '" << horizontalRadius << "' ry = '" << verticalRadius << "' "
		<< "cx = '" << center.x << "' cy = '" << center.y << "' "
		<< "stroke = '"<< GetColorHex(m_color) <<"' stroke-width = '5' "
		<< "fill = 'transparent'/>"
		<< endl;
}