#pragma once
#include "IOutlineStyle.h"

class CSimpleOutlineStyle: public IOutlineStyle
{
public:
	CSimpleOutlineStyle();
	std::optional<RGBAColor> GetColor()const;
	void SetColor(RGBAColor color);

	std::optional<size_t> GetLineWidth()const;
	void SetLineWidth(size_t lineWidth);
private:
	std::optional<RGBAColor> m_lineWidth = std::nullopt;
	std::optional<RGBAColor> m_outlineColor = std::nullopt;
};

