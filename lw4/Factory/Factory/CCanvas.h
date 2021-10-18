#pragma once
#include "ICanvas.h"

class CCanvas: public ICanvas
{
public:
	CCanvas(std::ostream& out);
	~CCanvas();
	void SetColor(Color color) override;
	void DrawLine(Point from, Point to) override;
	void DrawEllipse(Point center, double verticalRadius, double horizontalRadius) override;
private:
	std::ostream& m_output;
	Color m_color = Color::Black;
};

