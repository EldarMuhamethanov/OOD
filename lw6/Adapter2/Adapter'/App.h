#pragma once
#include "ShapeDrawindLib.h"
#include "ModernGraphicsLib.h"

// ������������ ���� ���������� (�������� ��� �����������)
namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter);

	void PaintPictureOnCanvas();

	void PaintPictureOnModernGraphicsRenderer();
}