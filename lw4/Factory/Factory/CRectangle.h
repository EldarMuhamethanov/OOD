#pragma once
#include "CShape.h"

class CRectangle: public CShape
{
public:
	CRectangle(Point leftTop, Point rightBottom, Color color);

	Point GetLeftTop() const;
	Point GetRightBottom() const;

	void Draw(ICanvas& canvas) const override;
private:
	Point m_leftTop;
	Point m_rightBottom;
};

