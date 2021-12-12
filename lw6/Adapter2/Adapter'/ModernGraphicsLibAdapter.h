#pragma once
#include "ModernGraphicsLib.h"
#include "GraphicsLib.h"

class ModernGraphicsLibAdapter: public graphics_lib::ICanvas, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	ModernGraphicsLibAdapter(std::ostream& out)
		: CModernGraphicsRenderer(out)
		, m_currPosition(0, 0)
	{
		BeginDraw();
	}

	void MoveTo(int x, int y) override
	{
		m_currPosition = modern_graphics_lib::CPoint(x, y);
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint endPoint(x, y);
		DrawLine(m_currPosition, endPoint);
		m_currPosition = endPoint;
	}

private:
	modern_graphics_lib::CPoint m_currPosition;
};

