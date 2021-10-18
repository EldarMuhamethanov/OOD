#include "CPainter.h"

using namespace std;

void CPainter::DrawPicture(CPictureDraft& draft, ICanvas& canvas)
{
	for (size_t i = 0; i < draft.GetShapeCount(); i++)
	{
		unique_ptr<IShape>& shape = draft.GetShape(i);
		canvas.SetColor(shape->GetColor());
		shape->Draw(canvas);
	}
}