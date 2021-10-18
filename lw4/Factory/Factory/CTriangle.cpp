#include "CTriangle.h"
#include <cmath>

using namespace std;

CTriangle::CTriangle(Point vertex1, Point vertex2, Point vertex3, Color color)
	: CShape(color)
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
	if (vertex1.x < 0 || vertex1.y < 0
		|| vertex2.x < 0 || vertex2.y < 0
		|| vertex3.x < 0 || vertex3.y < 0)
	{
		throw invalid_argument("invalid negative param in triangle");
	}

	double a = CalculateSideLength(vertex1, vertex2);
	double b = CalculateSideLength(vertex2, vertex3);
	double c = CalculateSideLength(vertex1, vertex3);

	if (a + b <= c
		|| a + c <= b
		|| b + c <= a)
	{
		throw invalid_argument("invalid vertex of triangle");
	}
}

double CTriangle::CalculateSideLength(Point vertex1, Point vertex2) const
{
	return sqrt(pow((vertex2.y - vertex1.y), 2) + pow((vertex2.x - vertex1.x), 2));
}

Point CTriangle::GetVertex1()const
{
	return m_vertex1;
}
Point CTriangle::GetVertex2()const
{
	return m_vertex2;
}
Point CTriangle::GetVertex3()const
{
	return m_vertex3;
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex1, m_vertex3);
}