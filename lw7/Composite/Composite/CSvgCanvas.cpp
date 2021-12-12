#include "CSvgCanvas.h"
#include <algorithm>

using namespace std;

CSvgCanvas::CSvgCanvas(std::ostream& out, double width, double height)
	: m_output(out)
{
	m_output << "<svg "
		<< "xmlns='http://www.w3.org/2000/svg' "
		<< "width='" << width << "' height='" << height << "' "
		<< "viewPort='0 0 " << width << " " << height << "'>"
		<< endl;
}

CSvgCanvas::~CSvgCanvas()
{
	m_output << "</svg>" << endl;
}

void CSvgCanvas::SetLineColor(std::optional<RGBAColor>  color)
{
	m_lineColor = color;
}
void CSvgCanvas::SetFillColor(std::optional<RGBAColor>  color)
{
	m_fillColor = color;
}
void CSvgCanvas::SetLineWidht(std::optional<size_t> width)
{
	m_lineWidth = width;
}

void CSvgCanvas::DrawLine(Point const& from, Point const& to)
{
	m_output
		<< "<line "
		<< "x1 = '" << from.x << "' y1 = '" << from.y
		<< "' x2 = '" << to.x << "' y2 = '" << to.y << "' "
		<< "stroke = '" << ConvertColorToString(m_lineColor) << "' stroke-width = '" << ConvertLineWidthToString(m_lineWidth) << "'/>"
		<< endl;
}
void CSvgCanvas::FillPolygon(std::vector<Point> const& vertexes)
{
	if (vertexes.size() == 0)
	{
		throw logic_error("FillPolygon with zero vertexes");
	}

	string vertexesString;
	for_each(vertexes.begin(), vertexes.end(), [&vertexesString](Point vertex) {
		vertexesString += to_string(vertex.x) + "," + to_string(vertex.y) + " ";
	});
	vertexesString.pop_back();

	m_output
		<< "<polygon "
		<< "points = '" << vertexesString << "' "
		<< "fill = '" << ConvertColorToString(m_fillColor) << "'/>";
}

void CSvgCanvas::DrawEllipse(double left, double top, double width, double height)
{
	Point center = { left + (width / 2), top + (height / 2) };
	m_output
		<< "<ellipse "
		<< "rx = '" << width / 2 << "' ry = '" << height / 2 << "' "
		<< "cx = '" << center.x << "' cy = '" << center.y << "' "
		<< "stroke = '" << ConvertColorToString(m_lineColor)<< "' stroke-width = '" << ConvertLineWidthToString(m_lineWidth) << "' "
		<< "fill = 'transparent'/>"
		<< endl;
}
void CSvgCanvas::FillEllipse(double left, double top, double width, double height)
{
	Point center = { left + (width / 2), top + (height / 2) };
	m_output
		<< "<ellipse "
		<< "rx = '" << width / 2 << "' ry = '" << height / 2 << "' "
		<< "cx = '" << center.x << "' cy = '" << center.y << "' "
		<< "fill = '" << ConvertColorToString(m_fillColor) <<  "'/>"
		<< endl;
}

std::string CSvgCanvas::ConvertColorToString(optional<RGBAColor> color) const
{
	if (!color)
		return "transparent";
	
	double r = ((*color >> 16) & 0xFF);
	double g = ((*color >> 8) & 0xFF);
	double b = ((*color) & 0xFF);

	return "rgb(" + to_string(r) + ", " + to_string(g) + ", " + to_string(b) + ")";
}

std::string CSvgCanvas::ConvertLineWidthToString(std::optional<size_t> width)const
{
	return to_string(width
		? *width
		: 0);
}