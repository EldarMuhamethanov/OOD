#include "CEllipse.h"

CEllipse::CEllipse(Point center, double horizontalRadius, double verticalRadius)
	: CShape()
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
	, m_center(center)
{}

RectD CEllipse::GetFrame()
{
	RectD rect;
	rect.left = m_center.x - m_horizontalRadius;
	rect.top = m_center.y - m_verticalRadius;
	rect.width = m_horizontalRadius + m_horizontalRadius;
	rect.height = m_verticalRadius + m_verticalRadius;
	return rect;
}

void CEllipse::SetFrame(const RectD& rect)
{
	m_center.x = rect.left + rect.width / 2;
	m_center.y = rect.top + rect.height / 2;
	m_verticalRadius = rect.height / 2;
	m_horizontalRadius = rect.width / 2;
}

void CEllipse::DrawShapeImpl(ICanvas& canvas)
{
	canvas.DrawEllipse(
		m_center.x - m_horizontalRadius,
		m_center.y - m_verticalRadius,
		m_horizontalRadius * 2,
		m_verticalRadius * 2
	);

	canvas.FillEllipse(
		m_center.x - m_horizontalRadius,
		m_center.y - m_verticalRadius,
		m_horizontalRadius * 2,
		m_verticalRadius * 2
	);
}