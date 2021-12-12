#include "CSlide.h"
#include <algorithm>

using namespace std;

CSlide::CSlide(double width, double height)
	: m_width(width)
	, m_height(height)
{}

double CSlide::GetWidth()const
{
	return m_width;
}
double CSlide::GetHeight()const
{
	return m_height;
}

size_t CSlide::GetShapesCount()const
{
	return m_shapes.size();
}
std::shared_ptr<IShape> CSlide::GetShapeAtIndex(size_t index)
{
	if (index >= GetShapesCount())
		throw std::out_of_range("position is out of range");
	
	return m_shapes[index];
}
void CSlide::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	if (position >= GetShapesCount())
		m_shapes.push_back(shape);
	else
		m_shapes.insert(m_shapes.begin() + position, shape);
	return;
}
void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index >= GetShapesCount())
		throw std::out_of_range("position is out of range");
	
	m_shapes.erase(m_shapes.begin() + index);
}

std::optional<RGBAColor> CSlide::GetBackgroundColor()const
{
	return m_color;
}
void CSlide::SetBackgroundColor(RGBAColor color)
{
	m_color = color;
}

void CSlide::Draw(ICanvas& canvas)
{
	if (m_color)
	{
		canvas.SetFillColor(m_color);

		canvas.FillPolygon({
			{0, 0},
			{m_width, 0},
			{m_width, m_height},
			{0, m_height},
		});
	}

	for_each(m_shapes.begin(), m_shapes.end(), [&canvas](shared_ptr<IShape>& shape) {
		shape->Draw(canvas);
	});
}