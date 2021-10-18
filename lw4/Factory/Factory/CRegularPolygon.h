#pragma once
#include "CShape.h"
class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(size_t vertexCount, Point center, size_t radius, Color color);

	size_t GetVertexCount();
	size_t GetRadius();
	Point GetCenter();

	void Draw(ICanvas& canvas) const override;

private:
	size_t m_vertexCount;
	size_t m_radius;
	Point m_center;
};

