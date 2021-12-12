#include "CShape.h"
#include <optional>

using namespace std;

IOutlineStyle& CShape::GetOutlineStyle()
{
	return *m_outlineStyle;
}
const IOutlineStyle& CShape::GetOutlineStyle()const
{
	return *m_outlineStyle;
}

IStyle& CShape::GetFillStyle()
{
	return *m_fillStyle;
}
const IStyle& CShape::GetFillStyle()const
{
	return *m_fillStyle;
}

std::shared_ptr<IGroupShape> CShape::GetGroup()
{
	return nullptr;
}
std::shared_ptr<const IGroupShape> CShape::GetGroup() const
{
	return nullptr;
}

void CShape::SetParent(std::shared_ptr<const IGroupShape> parent)
{
	m_parentShape = parent;
}

std::shared_ptr<const IGroupShape> CShape::GetParent() const
{
	return m_parentShape;
}

void CShape::Draw(ICanvas& canvas)
{
	canvas.SetLineColor(m_outlineStyle->GetColor());
	canvas.SetLineWidht(m_outlineStyle->GetLineWidth());
	canvas.SetFillColor(m_fillStyle->GetColor());

	DrawShapeImpl(canvas);
}