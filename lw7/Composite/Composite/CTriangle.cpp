#include "CTriangle.h"

CTriangle::CTriangle(Point vertex1, Point vertex2, Point vertex3)
	: CShape()
	, m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{}

RectD CTriangle::GetFrame()
{
	double minX = std::min({ m_vertex1.x, m_vertex2.x, m_vertex3.x });
	double minY = std::min({ m_vertex1.y, m_vertex2.y, m_vertex3.y });
	double maxX = std::max({ m_vertex1.x, m_vertex2.x, m_vertex3.x });
	double maxY = std::max({ m_vertex1.y, m_vertex2.y, m_vertex3.y });

	RectD rect;
	rect.left = minX;
	rect.top = minY;
	rect.width = maxX - minX;
	rect.height = maxY - minY;

	return rect;
}

void CTriangle::SetFrame(const RectD& rect)
{	
	RectD currentFrame = GetFrame();
	double widthCoef = rect.width / currentFrame.width;
	double heightCoef = rect.height / currentFrame.height;

	auto recalculateVertex = [widthCoef, heightCoef, currentFrame, rect](Point& vertex)
	{
		double vertexLeftRelativeFrame = vertex.x - currentFrame.left;
		double vertexTopRelativeFrame = vertex.y - currentFrame.top;
		vertex.x = rect.left + vertexLeftRelativeFrame * widthCoef;
		vertex.y = rect.top + vertexTopRelativeFrame * heightCoef;
	};
	recalculateVertex(m_vertex1);
	recalculateVertex(m_vertex2);
	recalculateVertex(m_vertex3);
}

void CTriangle::DrawShapeImpl(ICanvas& canvas)
{
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);

	canvas.FillPolygon({ m_vertex1, m_vertex2, m_vertex3 });
}