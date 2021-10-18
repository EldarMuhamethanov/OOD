#include "CShape.h"


CShape::CShape(Color shapeColor)
	: m_color(shapeColor)
{}

Color CShape::GetColor() const
{
	return m_color;
}
