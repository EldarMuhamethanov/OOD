#pragma once
#include <memory>
#include <string>
#include "CShape.h"

struct IShapeFactory
{
	virtual std::unique_ptr<IShape> CreateShape(const std::string& description) = 0;

	virtual ~IShapeFactory() = default;
};