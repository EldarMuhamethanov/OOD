#pragma once
#include "CShape.h"

class CTriangle: public CShape
{
public:
	CTriangle(Point vertex1, Point vertex2, Point vertex3);
	RectD GetFrame();
	void SetFrame(const RectD& rect);

	void DrawShapeImpl(ICanvas& canvas) override;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};

