#pragma once
#include "IStyle.h"

class IOutlineStyle: public IStyle
{
public:
	virtual std::optional<size_t> GetLineWidth()const = 0;
	virtual void SetLineWidth(size_t lineWidth) = 0;
};

