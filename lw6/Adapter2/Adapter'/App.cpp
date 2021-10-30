#include "App.h"
#include "ModernGraphicsLibAdapter.h"

using namespace std;

void app::PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	shape_drawing_lib::CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
	shape_drawing_lib::CRectangle rectangle({ 30, 40 }, 18, 24);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void app::PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void app::PaintPictureOnModernGraphicsRenderer()
{
	ModernGraphicsLibAdapter libAdapter(cout);
	shape_drawing_lib::CCanvasPainter painter(libAdapter);
	PaintPicture(painter);

	// TODO: при помощи существующей функции PaintPicture() нарисовать
	// картину на renderer
	// Подсказка: используйте паттерн "Адаптер"
}
