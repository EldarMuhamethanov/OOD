#pragma once
#include "CommonTypes.h"
#include <optional>
#include <vector>

class ICanvas
{
public:
	virtual void SetLineColor(std::optional<RGBAColor> color) = 0;
	virtual void SetFillColor(std::optional<RGBAColor> color) = 0;
	virtual void SetLineWidht(std::optional<size_t> width) = 0;

	virtual void DrawLine(Point const& from, Point const& to) = 0;
	virtual void FillPolygon(std::vector<Point> const& vertexes) = 0;

	virtual void DrawEllipse(double left, double top, double width, double height) = 0;
	virtual void FillEllipse(double left, double top, double width, double height) = 0;

	virtual ~ICanvas() = default;
};

