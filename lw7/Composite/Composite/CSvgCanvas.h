#pragma once
#include "ICanvas.h"
#include <optional>
#include <string>

class CSvgCanvas : public ICanvas
{
public:
	CSvgCanvas(std::ostream& out, double width, double height);
	~CSvgCanvas();
	void SetLineColor(std::optional<RGBAColor>  color) override;
	void SetFillColor(std::optional<RGBAColor>  color) override;
	void SetLineWidht(std::optional<size_t> width) override;

	void DrawLine(Point const& from, Point const& to) override;
	void FillPolygon(std::vector<Point> const& vertexes) override;

	void DrawEllipse(double left, double top, double width, double height) override;
	void FillEllipse(double left, double top, double width, double height) override;

private:
	std::string ConvertColorToString(std::optional<RGBAColor> color)const;
	std::string ConvertLineWidthToString(std::optional<size_t> width)const;

	std::ostream& m_output;

	std::optional<RGBAColor> m_lineColor = std::nullopt;
	std::optional<RGBAColor> m_fillColor = std::nullopt;
	std::optional<size_t> m_lineWidth = std::nullopt;
};