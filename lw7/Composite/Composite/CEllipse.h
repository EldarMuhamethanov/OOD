#pragma once
#include "CShape.h"

class CEllipse: public CShape
{
public:
	CEllipse(Point center, double horizontalRadius, double verticalRadius);
	RectD GetFrame();
	void SetFrame(const RectD& rect);

	void DrawShapeImpl(ICanvas& canvas) override;

private:
	Point m_center;
	double m_horizontalRadius;
	double m_verticalRadius;
};

