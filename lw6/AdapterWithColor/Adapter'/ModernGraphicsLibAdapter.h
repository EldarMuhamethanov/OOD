#pragma once
#include "ModernGraphicsLib.h"
#include "GraphicsLib.h"

class ModernGraphicsLibAdapter: public graphics_lib::ICanvas
{
	static constexpr float DEFAULT_ALPHA_CHANEL = 1;
public:
	ModernGraphicsLibAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
		: m_renderer(renderer)
		, m_currPosition(0, 0)
		, m_color(0, 0, 0, DEFAULT_ALPHA_CHANEL)
	{
		m_renderer.BeginDraw();
	}

	void SetColor(uint32_t rgbColor) override
	{
		double r = ((rgbColor >> 16) & 0xFF) / 255.0;
		double g = ((rgbColor >> 8) & 0xFF) / 255.0;
		double b = ((rgbColor) & 0xFF) / 255.0;
		m_color = modern_graphics_lib::CRGBAColor((float)r, (float)g, (float)b, DEFAULT_ALPHA_CHANEL);
	}

	void MoveTo(int x, int y) override
	{
		m_currPosition = modern_graphics_lib::CPoint(x, y);
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint endPoint(x, y);
		m_renderer.DrawLine(m_currPosition, endPoint, m_color);
		m_currPosition = endPoint;
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::CPoint m_currPosition;
	modern_graphics_lib::CRGBAColor m_color;
};

