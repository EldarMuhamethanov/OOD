#pragma once
#include "IGroupShape.h"
#include "CSimpleFillStyle.h"
#include "CSimpleOutlineStyle.h"
#include "CGroupOutlineColor.h"
#include "CGroupFillStyle.h"

class CGroupShape: public IGroupShape
{
public:
	CGroupShape() {
		m_fillStyle = std::make_shared<CGroupFillStyle>(m_shapes);
		m_outlineStyle = std::make_shared<CGroupOutlineColor>(m_shapes);
	};

	RectD GetFrame() override;
	void SetFrame(const RectD& rect) override;

	IOutlineStyle& GetOutlineStyle() override;
	const IOutlineStyle& GetOutlineStyle()const override;

	IStyle& GetFillStyle() override;
	const IStyle& GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	void SetParent(std::shared_ptr<const IGroupShape> parent) override;
	std::shared_ptr<const IGroupShape> GetParent()const override;

	size_t GetShapesCount()const override;
	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

	void Draw(ICanvas& canvas) override;
private:
	bool CanInsertShape(std::shared_ptr<const IShape> shape);

	std::shared_ptr<IStyle> m_fillStyle;
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<const IGroupShape> m_parentShape = nullptr;
};

