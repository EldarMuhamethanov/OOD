#include "CGroupFillStyle.h"
#include <algorithm>

using namespace std;

CGroupFillStyle::CGroupFillStyle(std::vector<std::shared_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{}

std::optional<RGBAColor> CGroupFillStyle::GetColor()const
{
	std::optional<RGBAColor> color = nullopt;
	for (auto& shape : m_shapes)
	{
		optional<RGBAColor> currColor = shape->GetFillStyle().GetColor();
		if (!currColor)
		{
			return nullopt;
		}
		if (!color)
		{
			color = currColor;
			continue;
		}
		if (*color != currColor)
		{
			return nullopt;
		}
	}
	return color;
}
void CGroupFillStyle::SetColor(RGBAColor color)
{
	for (auto& shape : m_shapes)
	{
		shape->GetFillStyle().SetColor(color);
	}
}