#pragma once
#include "IOutlineStyle.h"
#include "IShape.h"
#include <vector>

class CGroupOutlineColor : public IOutlineStyle
{
public:
	CGroupOutlineColor(std::vector<std::shared_ptr<IShape>>& shapes);

	std::optional<RGBAColor> GetColor()const override;
	void SetColor(RGBAColor color) override;

	std::optional<size_t> GetLineWidth()const override;
	void SetLineWidth(size_t lineWidth) override;
private:
	std::vector<std::shared_ptr<IShape>>& m_shapes;
};

