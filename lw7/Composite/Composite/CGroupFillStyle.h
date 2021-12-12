#pragma once
#include "IStyle.h"
#include "IShape.h"
#include <vector>

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(std::vector<std::shared_ptr<IShape>>& shapes);

	std::optional<RGBAColor> GetColor()const override;
	void SetColor(RGBAColor color) override;
private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
};

