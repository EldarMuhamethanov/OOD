#pragma once
#include "CShape.h"

class CTriangle: public CShape
{
public:
	CTriangle(Point vertex1, Point vertex2, Point vertex3, Color color);

	Point GetVertex1()const;
	Point GetVertex2()const;
	Point GetVertex3()const;

	double CalculateSideLength(Point vertex1, Point vertex2) const;

	void Draw(ICanvas& canvas) const override;
private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};

