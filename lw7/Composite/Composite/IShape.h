#pragma once
#include "IDrawable.h"
#include "CommonTypes.h"
#include "IOutlineStyle.h"
#include "IStyle.h"

class IGroupShape;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual IOutlineStyle& GetOutlineStyle() = 0;
	virtual const IOutlineStyle& GetOutlineStyle()const = 0;

	virtual IStyle& GetFillStyle() = 0;
	virtual const IStyle& GetFillStyle()const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual void SetParent(std::shared_ptr<const IGroupShape> parent) = 0;
	virtual std::shared_ptr<const IGroupShape> GetParent()const = 0;

	virtual ~IShape() = default;
};
