#include <iostream>
#include <fstream>
#include "CTriangle.h"
#include "CEllipse.h"
#include "CRectangle.h"
#include "CGroupShape.h"
#include "CommonTypes.h"
#include "CSvgCanvas.h"
#include "CSlide.h"

using namespace std;

int main()
{
	CSlide slide(1000, 800);
	ofstream out("result.svg");
	CSvgCanvas canvas(out, 1000, 800);

	shared_ptr<IShape> ground = make_shared<CRectangle>(Point{ 0, 600 }, Point{ 1000, 800 });
	ground->GetFillStyle().SetColor(0x524E2A);
	shared_ptr<IShape> house = make_shared<CRectangle>(Point{ 100, 400 }, Point{ 500, 700 });
	house->GetFillStyle().SetColor(0x793119);
	shared_ptr<IShape> window = make_shared<CRectangle>(Point{ 200, 470 }, Point{ 400, 630 });
	window->GetFillStyle().SetColor(0x46F5F4);
	shared_ptr<IShape> roof = make_shared<CTriangle>(Point{ 90, 400 }, Point{ 510, 400}, Point{ 300, 200 });
	roof->GetFillStyle().SetColor(0x11AA4E);
	shared_ptr<IShape> lake = make_shared<CEllipse>(Point{ 700, 700 }, 120, 65);
	lake->GetFillStyle().SetColor(0x46F5F4);
	shared_ptr<IShape> sun = make_shared<CEllipse>(Point{ 800, 150}, 100, 100);
	sun->GetFillStyle().SetColor(0xE7EF32);
	
	shared_ptr<IGroupShape> picture = make_shared<CGroupShape>();
	picture->InsertShape(ground);
	picture->InsertShape(house);
	picture->InsertShape(window);
	picture->InsertShape(roof);
	picture->InsertShape(lake);
	picture->InsertShape(sun);

	slide.InsertShape(picture);
	slide.SetBackgroundColor(0x000000);

	picture->GetFillStyle().SetColor(0x46F5F4);
	//picture->GetOutlineStyle().SetColor(0x46F5F4);
	//picture->GetOutlineStyle().SetLineWidth(9);
	//RectD frame = picture->GetFrame();
	picture->SetFrame(RectD{ 0, 0, 400, 300 });
	slide.Draw(canvas);

}