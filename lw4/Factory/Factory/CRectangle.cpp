#include "CRectangle.h"
#include <stdexcept>

using namespace std;

CRectangle::CRectangle(Point leftTop, Point rightBottom, Color color)
	: CShape(color)
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{
	if (leftTop.x < 0 || leftTop.y < 0
		|| rightBottom.x < 0 || rightBottom.y < 0)
	{
		throw invalid_argument("invalid negative param in rectangle");
	}
}

Point CRectangle::GetLeftTop() const
{
	return m_leftTop;
}
Point CRectangle::GetRightBottom() const
{
	return m_rightBottom;
}

void CRectangle::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_leftTop, { m_rightBottom.x, m_leftTop.y });
	canvas.DrawLine({m_rightBottom.x, m_leftTop.y}, m_rightBottom);
	canvas.DrawLine(m_leftTop, { m_leftTop.x, m_rightBottom.y });
	canvas.DrawLine({ m_leftTop.x, m_rightBottom.y }, m_rightBottom);
}