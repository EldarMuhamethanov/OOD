#include "CSimpleFillStyle.h"

CSimpleFillStyle::CSimpleFillStyle() {};

std::optional<RGBAColor> CSimpleFillStyle::GetColor()const
{
	return m_fillColor;
}
void CSimpleFillStyle::SetColor(RGBAColor color)
{
	m_fillColor = color;
}
