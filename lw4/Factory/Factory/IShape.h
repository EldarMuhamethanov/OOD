#pragma once
#include "Color.h"
#include "ICanvas.h"

class IShape
{
public:
	virtual Color GetColor() const = 0;
	virtual void Draw(ICanvas& canvas) const = 0;
};

