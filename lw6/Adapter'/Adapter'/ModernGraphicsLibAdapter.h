#pragma once
#include "ModernGraphicsLib.h"
#include "GraphicsLib.h"

class ModernGraphicsLibAdapter: public graphics_lib::ICanvas
{
public:
	ModernGraphicsLibAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
		: m_renderer(renderer)
		, m_currPosition(0, 0)
	{
		m_renderer.BeginDraw();
	}

	void MoveTo(int x, int y) override
	{
		m_currPosition = modern_graphics_lib::CPoint(x, y);
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint endPoint(x, y);
		m_renderer.DrawLine(m_currPosition, endPoint);
		m_currPosition = endPoint;
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::CPoint m_currPosition;
};

