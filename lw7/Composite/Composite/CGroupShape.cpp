#include "CGroupShape.h"
#include <stdexcept>
#include <algorithm>

using namespace std;

RectD CGroupShape::GetFrame()
{
	if (GetShapesCount() == 0)
		throw logic_error("group does not have any shape");

	double minX = numeric_limits<size_t>::max();
	double minY = numeric_limits<size_t>::max();
	double maxX = numeric_limits<size_t>::min();
	double maxY = numeric_limits<size_t>::min();

	for_each(m_shapes.begin(), m_shapes.end(), [&minX, &minY, &maxX, &maxY](shared_ptr<IShape>& shape) {
		RectD rect = shape->GetFrame();
		minX = std::min({ minX, rect.left });
		minY = std::min({ minY, rect.top });
		maxX = std::max({ maxX, rect.left + rect.width });
		maxY = std::max({ maxY, rect.top + rect.height });
	});

	return {
		minX,
		minY,
		maxX - minX,
		maxY - minY
	};
}
void CGroupShape::SetFrame(const RectD& rect)
{
	if (GetShapesCount() == 0)
		throw logic_error("group does not have any shape");

	RectD currentFrame = GetFrame();

	double widthCoef = rect.width / currentFrame.width;
	double heightCoef = rect.height / currentFrame.height;

	for_each(m_shapes.begin(), m_shapes.end(), [rect, currentFrame, widthCoef, heightCoef](shared_ptr<IShape>& shape) {
		RectD shapeFrame = shape->GetFrame();
		double leftOffsetRelativeCurrentFrame = shapeFrame.left - currentFrame.left;
		double topOffsetRelativeCurrentFrame = shapeFrame.top - currentFrame.top;
		RectD newFrame = {
			rect.left + (leftOffsetRelativeCurrentFrame * widthCoef),
			rect.top + (topOffsetRelativeCurrentFrame * heightCoef),
			shapeFrame.width * widthCoef,
			shapeFrame.height * heightCoef,
		};
		shape->SetFrame(newFrame);
	});
}

IOutlineStyle& CGroupShape::GetOutlineStyle()
{
	return *m_outlineStyle.get();
}
const IOutlineStyle& CGroupShape::GetOutlineStyle()const
{
	return *m_outlineStyle.get();
}

IStyle& CGroupShape::GetFillStyle()
{
	return *m_fillStyle.get();
}
const IStyle& CGroupShape::GetFillStyle()const
{
	return *m_fillStyle.get();
}
std::shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return shared_from_this();
}
std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return shared_from_this();
}

void CGroupShape::SetParent(std::shared_ptr<const IGroupShape> parent)
{
	m_parentShape = parent;
}
std::shared_ptr<const IGroupShape> CGroupShape::GetParent() const
{
	return m_parentShape;
}
size_t CGroupShape::GetShapesCount()const
{
	return m_shapes.size();
}
void CGroupShape::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	if (CanInsertShape(shape))
	{
		if (position >= GetShapesCount())
			m_shapes.push_back(shape);
		else
			m_shapes.insert(m_shapes.begin() + position, shape);
		shape->SetParent(GetGroup());
		return;
	}
	throw logic_error("try to insert one of the parent of shape");
}
std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index)
{
	if (index >= GetShapesCount())
		throw std::out_of_range("position is out of range");
	
	return m_shapes[index];
}
void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	if (index >= GetShapesCount())
		throw std::out_of_range("position is out of range");

	m_shapes[index]->SetParent(nullptr);
	m_shapes.erase(m_shapes.begin() + index);
}

void CGroupShape::Draw(ICanvas& canvas)
{
	for_each(m_shapes.begin(), m_shapes.end(), [&canvas](shared_ptr<IShape> shape) {
		shape->Draw(canvas);
	});
}

bool CGroupShape::CanInsertShape(std::shared_ptr<const IShape> shape)
{
	shared_ptr<const IGroupShape> currentShape = GetGroup();
	while (currentShape != nullptr)
	{
		if (currentShape == shape)
			return false;
		currentShape = currentShape->GetParent();
	}
	return true;
}