#pragma once
#include "ShapeDrawindLib.h"
#include "ModernGraphicsLib.h"

// Пространство имен приложения (доступно для модификации)
namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter);

	void PaintPictureOnCanvas();

	void PaintPictureOnModernGraphicsRenderer();
}
