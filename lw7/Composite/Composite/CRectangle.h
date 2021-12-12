#pragma once
#include "CShape.h"

class CRectangle: public CShape
{
public:
	CRectangle(Point leftTop, Point rightBottom);
	RectD GetFrame();
	void SetFrame(const RectD& rect);

	void DrawShapeImpl(ICanvas& canvas) override;
private:
	Point m_leftTop;
	Point m_rightBottom;
};

