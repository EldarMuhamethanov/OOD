#include "CEllipse.h"
#include <stdexcept>

using namespace std;

CEllipse::CEllipse(Point center, double horizontalRadius, double verticalRadius, Color color)
	: CShape(color)
	, m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
	if (center.x < 0 || center.y < 0
		|| horizontalRadius < 0 || verticalRadius < 0)
	{
		throw invalid_argument("invalid negative param in ellipse");
	}
}

Point CEllipse::GetCenter()
{
	return m_center;
}
double CEllipse::GetHorizontalRadius()
{
	return m_horizontalRadius;
}
double CEllipse::GetVerticalRadius()
{
	return m_verticalRadius;
}

void CEllipse::Draw(ICanvas& canvas) const
{
	canvas.DrawEllipse(m_center, m_verticalRadius, m_horizontalRadius);
}