#pragma once
#include "CShape.h"

class CEllipse: public CShape
{
public:
	CEllipse(Point center, double horizontalRadius, double verticalRadius, Color color);

	Point GetCenter();
	double GetHorizontalRadius(); 
	double GetVerticalRadius();

	void Draw(ICanvas& canvas) const override;
private:
	Point m_center;
	double m_horizontalRadius;
	double m_verticalRadius;
};

