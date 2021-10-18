#include <iostream>
#include <fstream>
#include "CShapeFactory.h"
#include "CDesigner.h"
#include "CPainter.h"
#include "CCanvas.h"

using namespace std;

int main()
{
	ofstream result("result.svg");
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);

	CPictureDraft draft = designer.CreateDraft(cin);

	CCanvas canvas(result);

	CPainter painter;

	painter.DrawPicture(draft, canvas);
}