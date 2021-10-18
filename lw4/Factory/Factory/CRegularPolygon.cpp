#include "CRegularPolygon.h"
#include <cmath>
#include <vector>

using namespace std;

CRegularPolygon::CRegularPolygon(size_t vertexCount, Point center, size_t radius, Color color)
	: CShape(color)
	, m_vertexCount(vertexCount)
	, m_center(center)
	, m_radius(radius)
{
	if (center.x < 0 || center.y < 0
		|| vertexCount < 0 || radius < 0)
	{
		throw invalid_argument("invalid negative param in regular polygon");
	}
	if (vertexCount < 3) {
		throw invalid_argument("invalid count of vertex < 3");
	}
}

size_t CRegularPolygon::GetVertexCount()
{
	return m_vertexCount;
}
size_t CRegularPolygon::GetRadius()
{
	return m_radius;
}
Point CRegularPolygon::GetCenter()
{
	return m_center;
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	double centerAngle = 2 * 3.14 / m_vertexCount;

	vector<Point> points;

	for (size_t i = 0; i < m_vertexCount; i++)
	{
		points.push_back({
			 m_center.x + m_radius * sin(centerAngle * i),
			 m_center.y + m_radius * cos(centerAngle * i)
		});
	}
	points.push_back(points[0]);

	for (size_t i = 1; i < points.size(); i++)
		canvas.DrawLine(points[i], points[i - 1]);
}