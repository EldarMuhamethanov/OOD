#pragma once
#include "IShapeFactory.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CEllipse.h"
#include "CRegularPolygon.h"
#include "IShape.h"
#include <vector>

const std::string RECTANGLE_STRING = "rectangle";
const std::string TRIANGLE_STRING = "triangle";
const std::string ELLIPSE_STRING = "ellipse";
const std::string POLYGON_STRING = "polygon";

const std::string RED_COLOR_STRING = "red";
const std::string GREEN_COLOR_STRING = "green";
const std::string BLUE_COLOR_STRING = "blue";
const std::string PINK_COLOR_STRING = "pink";
const std::string YELLOW_COLOR_STRING = "yellow";
const std::string BLACK_COLOR_STRING = "black";

class CShapeFactory: public IShapeFactory
{
public:
	CShapeFactory() {};
	std::unique_ptr<IShape> CreateShape(const std::string& description) override;
private:
	
	std::unique_ptr<CRectangle> CreateRectangle(std::vector<std::string> const& params) const;
	std::unique_ptr<CTriangle> CreateTriangle(std::vector<std::string> const& params) const;
	std::unique_ptr<CEllipse> CreateEllipse(std::vector<std::string> const& params) const;
	std::unique_ptr<CRegularPolygon> CreateRegularPolygon(std::vector<std::string> const& params) const;

	std::vector<std::string> GetParams(std::string const& str) const;

	Color GetColor(std::string const& color) const;
	Point GetPoint(std::string const& x, std::string const& y) const;
};

