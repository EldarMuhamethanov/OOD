#include "CRectangle.h"

CRectangle::CRectangle(Point leftTop, Point rightBottom)
	: CShape()
	, m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{}

RectD CRectangle::GetFrame()
{
	RectD rect;
	rect.left = m_leftTop.x;
	rect.top = m_leftTop.y;
	rect.width = m_rightBottom.x - m_leftTop.x;
	rect.height = m_rightBottom.y - m_leftTop.y;
	return rect;
}
void CRectangle::SetFrame(const RectD& rect)
{
	m_leftTop.x = rect.left;
	m_leftTop.y = rect.top;
	m_rightBottom.x = rect.left + rect.width;
	m_rightBottom.y = rect.top + rect.height;
}

void CRectangle::DrawShapeImpl(ICanvas& canvas)
{
	canvas.DrawLine(m_leftTop, { m_rightBottom.x, m_leftTop.y });
	canvas.DrawLine({ m_rightBottom.x, m_leftTop.y }, m_rightBottom);
	canvas.DrawLine(m_rightBottom, { m_leftTop.x, m_rightBottom.y });
	canvas.DrawLine(m_leftTop, { m_leftTop.x, m_rightBottom.y });

	canvas.FillPolygon({
		{m_leftTop},
		{ m_rightBottom.x, m_leftTop.y },
		m_rightBottom,
		{ m_leftTop.x, m_rightBottom.y }
	});
}