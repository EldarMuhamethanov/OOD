#pragma once
#include "IShape.h"
#include <memory>



class CShape: public IShape
{
public:
	CShape(Color shapeColor);
	Color GetColor() const override;
	virtual ~CShape() = default;
private:
	Color m_color;
};

