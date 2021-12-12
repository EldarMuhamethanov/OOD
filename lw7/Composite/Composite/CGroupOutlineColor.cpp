#include "CGroupOutlineColor.h"
#include <algorithm>

using namespace std;

CGroupOutlineColor::CGroupOutlineColor(std::vector<std::shared_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{}

std::optional<RGBAColor> CGroupOutlineColor::GetColor()const
{
	std::optional<RGBAColor> color = nullopt;
	for (auto& shape : m_shapes)
	{
		auto currColor = shape->GetOutlineStyle().GetColor();
		if (!currColor)
		{
			return nullopt;
		}
		if (!color)
		{
			color = currColor;
			continue;
		}
		if (color != currColor)
		{
			return nullopt;
		}
	}
	return color;
}
void CGroupOutlineColor::SetColor(RGBAColor color)
{
	for (auto& shape : m_shapes)
	{
		shape->GetOutlineStyle().SetColor(color);
	}
}

std::optional<size_t> CGroupOutlineColor::GetLineWidth()const
{
	std::optional<size_t> lineWidth = nullopt;
	for (auto& shape : m_shapes)
	{
		auto currLineWidth = shape->GetOutlineStyle().GetLineWidth();
		if (!currLineWidth)
		{
			return nullopt;
		}
		if (!lineWidth)
		{
			lineWidth = currLineWidth;
			continue;
		}
		if (lineWidth != currLineWidth)
		{
			return nullopt;
		}
	}
	return lineWidth;
}
void CGroupOutlineColor::SetLineWidth(size_t lineWidth)
{
	for (auto& shape : m_shapes)
	{
		shape->GetOutlineStyle().SetLineWidth(lineWidth);
	}
}