#pragma once
#include "IShape.h"
#include "CSimpleFillStyle.h"
#include "CSimpleOutlineStyle.h"

class CShape: public IShape
{
public:
	CShape() {};
	IOutlineStyle& GetOutlineStyle() override;
	const IOutlineStyle& GetOutlineStyle()const override;

	IStyle& GetFillStyle() override;
	const IStyle& GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	void Draw(ICanvas& canvas) override;

	void SetParent(std::shared_ptr<const IGroupShape> parent) override;
	std::shared_ptr<const IGroupShape> GetParent()const override;

	virtual void DrawShapeImpl(ICanvas& canvas) = 0;

private:
	std::shared_ptr<IStyle> m_fillStyle = std::make_shared<CSimpleFillStyle>();
	std::shared_ptr<IOutlineStyle> m_outlineStyle = std::make_shared<CSimpleOutlineStyle>();
	std::shared_ptr<const IGroupShape> m_parentShape = nullptr;
};

