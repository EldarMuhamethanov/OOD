#include "CShapeFactory.h"
#include <sstream>

using namespace std;

unique_ptr<IShape> CShapeFactory::CreateShape(const string& description)
{
	vector<string> params = GetParams(description);
	const string shapeStr = params[0];
	if (shapeStr == RECTANGLE_STRING)
		return CreateRectangle(params);
	if (shapeStr == TRIANGLE_STRING)
		return CreateTriangle(params);
	if (shapeStr == ELLIPSE_STRING)
		return CreateEllipse(params);
	if (shapeStr == POLYGON_STRING)
		return CreateRegularPolygon(params);

	throw invalid_argument("invalid shape name");
}

unique_ptr<CRectangle> CShapeFactory::CreateRectangle(vector<string> const& params) const
{
	if (params.size() != 6) {
		throw invalid_argument("invalid count of arguments rectangle");
	}
	return make_unique<CRectangle>(
		GetPoint(params[2], params[3]),
		GetPoint(params[4], params[5]),
		GetColor(params[1])
	);
}

unique_ptr<CTriangle> CShapeFactory::CreateTriangle(vector<string> const& params) const
{
	if (params.size() != 8) {
		throw invalid_argument("invalid count of arguments triangle");
	}
	return make_unique<CTriangle>(
		GetPoint(params[2], params[3]),
		GetPoint(params[4], params[5]),
		GetPoint(params[6], params[7]),
		GetColor(params[1])
	);
}

unique_ptr<CEllipse> CShapeFactory::CreateEllipse(vector<string> const& params) const
{
	if (params.size() != 6) {
		throw invalid_argument("invalid count of arguments ellipse");
	}
	return make_unique<CEllipse>(
		GetPoint(params[2], params[3]),
		stoi(params[4]),
		stoi(params[5]),
		GetColor(params[1])
	);
}

std::unique_ptr<CRegularPolygon> CShapeFactory::CreateRegularPolygon(std::vector<std::string> const& params) const
{
	if (params.size() != 6) {
		throw invalid_argument("invalid count of arguments polygon");
	}
	return make_unique<CRegularPolygon>(
		stoi(params[2]),
		GetPoint(params[3], params[4]),
		stoi(params[5]),
		GetColor(params[1])
	);
}

vector<string> CShapeFactory::GetParams(const string& str) const
{
	vector<string> params;
	istringstream strm(str);
	while (!strm.eof())
	{
		string token;
		strm >> token;
		params.push_back(token);
	}
	return params;
}

Color CShapeFactory::GetColor(string const& color) const
{
	if (color == RED_COLOR_STRING)
		return Color::Red;
	if (color == GREEN_COLOR_STRING)
		return Color::Green;
	if (color == PINK_COLOR_STRING)
		return Color::Pink;
	if (color == PINK_COLOR_STRING)
		return Color::Pink;
	if (color == YELLOW_COLOR_STRING)
		return Color::Yellow;
	if (color == BLACK_COLOR_STRING)
		return Color::Black;

	throw invalid_argument("unknown color");
}

Point CShapeFactory::GetPoint(string const& x, string const& y) const
{
	return {stod(x), stod(y) };
}