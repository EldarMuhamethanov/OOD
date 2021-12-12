#pragma once
#include "IStyle.h"

class CSimpleFillStyle: public IStyle
{
public:
	CSimpleFillStyle();

	std::optional<RGBAColor> GetColor()const override;
	void SetColor(RGBAColor color) override;
private:
	std::optional<RGBAColor> m_fillColor = std::nullopt;
};

