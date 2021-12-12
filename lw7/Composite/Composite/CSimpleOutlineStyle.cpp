#include "CSimpleOutlineStyle.h"

CSimpleOutlineStyle::CSimpleOutlineStyle() {}

std::optional<RGBAColor> CSimpleOutlineStyle::GetColor()const
{
	return m_outlineColor;
}
void CSimpleOutlineStyle::SetColor(RGBAColor color)
{
	m_outlineColor = color;
}

std::optional<size_t> CSimpleOutlineStyle::GetLineWidth()const
{
	return m_lineWidth;
}

void CSimpleOutlineStyle::SetLineWidth(size_t lineWidth)
{
	m_lineWidth = lineWidth;
}