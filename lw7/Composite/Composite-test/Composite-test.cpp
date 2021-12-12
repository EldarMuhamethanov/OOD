#define CATCH_CONFIG_MAIN
#include "../../../Catch2/catch.hpp"
#include "../Composite/CEllipse.h"
#include "../Composite/CRectangle.h"
#include "../Composite/CTriangle.h"
#include "../Composite/CGroupShape.h"
#include "../Composite/CSvgCanvas.h"
#include "../Composite/CSlide.h"
#include "../Composite/CommonTypes.h"
#include <memory>

using namespace std;

void CheckFrame(RectD frame, double left, double top, double width, double height)
{
	REQUIRE(frame.left == left);
	REQUIRE(frame.top == top);
	REQUIRE(frame.width == width);
	REQUIRE(frame.height == height);
}

SCENARIO("test Ellipse")
{
	shared_ptr<IShape> ellipse = make_shared<CEllipse>(Point{10, 10}, 7, 5);
	CheckFrame(ellipse->GetFrame(), 3, 5, 14, 10);
	ellipse->SetFrame(RectD{ 5, 5, 16, 12 });
	CheckFrame(ellipse->GetFrame(), 5, 5, 16, 12);

	REQUIRE(ellipse->GetGroup() == nullptr);
}

SCENARIO("test Rectangle")
{
	shared_ptr<IShape> rectangle = make_shared<CRectangle>(Point{ 10, 10 }, Point{20, 20});
	CheckFrame(rectangle->GetFrame(), 10, 10, 10, 10);
	rectangle->SetFrame(RectD{ 5, 6, 7, 8 });
	CheckFrame(rectangle->GetFrame(), 5, 6, 7, 8);

	REQUIRE(rectangle->GetGroup() == nullptr);
}

SCENARIO("test Triangle")
{
	shared_ptr<IShape> triangle = make_shared<CTriangle>(Point{ 10, 10 }, Point{ 19, 22 }, Point{15, 17});
	CheckFrame(triangle->GetFrame(), 10, 10, 9, 12);
	triangle->SetFrame(RectD{ 5, 6, 7, 8 });
	CheckFrame(triangle->GetFrame(), 5, 6, 7, 8);

	REQUIRE(triangle->GetGroup() == nullptr);
}

SCENARIO("test simple style")
{
	WHEN("test fill style")
	{
		CSimpleFillStyle fillStyle;
		auto fillColor = fillStyle.GetColor();
		REQUIRE(fillColor == nullopt);
		fillStyle.SetColor(0x123456);
		REQUIRE(*fillStyle.GetColor() == 0x123456);
	}
	WHEN("test outline style")
	{
		CSimpleOutlineStyle outlineStyle;
		auto outlineColor = outlineStyle.GetColor();
		auto lineWidth = outlineStyle.GetLineWidth();
		REQUIRE(outlineColor == nullopt);
		REQUIRE(outlineColor == nullopt);
		outlineStyle.SetColor(0x123456);
		outlineStyle.SetLineWidth(10);
		REQUIRE(*outlineStyle.GetColor() == 0x123456);
		REQUIRE(*outlineStyle.GetLineWidth() == 10);
	}
}

SCENARIO("test shape group")
{
	shared_ptr<IGroupShape> group = make_shared<CGroupShape>();
	REQUIRE_THROWS(group->GetFrame());
	REQUIRE_THROWS(group->SetFrame(RectD{ 1, 2, 3, 4 }));

	REQUIRE(group->GetGroup() == group);
	REQUIRE(group->GetParent() == nullptr);
	REQUIRE(group->GetShapesCount() == 0);

	shared_ptr<IShape> rectangle = make_shared<CRectangle>(Point{ 10, 10 }, Point{ 20, 20 });
	shared_ptr<IShape> triangle = make_shared<CTriangle>(Point{ 10, 10 }, Point{ 19, 22 }, Point{ 15, 17 });
	shared_ptr<IShape> ellipse = make_shared<CEllipse>(Point{ 10, 10 }, 7, 5);

	group->InsertShape(rectangle);
	group->InsertShape(triangle);
	group->InsertShape(ellipse);

	REQUIRE(group->GetShapesCount() == 3);
	CheckFrame(group->GetFrame(), 3, 5, 17, 17);
	group->SetFrame(RectD{ 1, 2, 3, 4 });
	CheckFrame(group->GetFrame(), 1, 2, 3, 4);

	REQUIRE(group->GetShapeAtIndex(1) == triangle);
	REQUIRE_THROWS(group->GetShapeAtIndex(3));

	group->RemoveShapeAtIndex(0);
	REQUIRE(group->GetShapesCount() == 2);
	REQUIRE(group->GetShapeAtIndex(0) == triangle);
	REQUIRE(group->GetShapeAtIndex(1) == ellipse);
}

SCENARIO("test group style")
{
	shared_ptr<IShape> rectangle = make_shared<CRectangle>(Point{ 10, 10 }, Point{ 20, 20 });
	shared_ptr<IShape> triangle = make_shared<CTriangle>(Point{ 10, 10 }, Point{ 19, 22 }, Point{ 15, 17 });
	shared_ptr<IShape> ellipse = make_shared<CEllipse>(Point{ 10, 10 }, 7, 5);
	vector<shared_ptr<IShape>> shapes;
	shapes.push_back(rectangle);
	shapes.push_back(triangle);
	shapes.push_back(ellipse);

	WHEN("test fill style")
	{
		CGroupFillStyle fillStyle(shapes);
		REQUIRE(fillStyle.GetColor() == nullopt);

		rectangle->GetFillStyle().SetColor(0x111111);
		triangle->GetFillStyle().SetColor(0x222222);
		ellipse->GetFillStyle().SetColor(0x333333);

		REQUIRE(fillStyle.GetColor() == nullopt);
		fillStyle.SetColor(0x444444);
		REQUIRE(*fillStyle.GetColor() == 0x444444);
	}
	WHEN("test outline style")
	{
		CGroupOutlineColor outlineStyle(shapes);
		REQUIRE(outlineStyle.GetColor() == nullopt);
		REQUIRE(outlineStyle.GetLineWidth() == nullopt);

		rectangle->GetOutlineStyle().SetColor(0x111111);
		triangle->GetOutlineStyle().SetColor(0x222222);
		ellipse->GetOutlineStyle().SetColor(0x333333);

		REQUIRE(outlineStyle.GetColor() == nullopt);
		outlineStyle.SetColor(0x444444);
		REQUIRE(*outlineStyle.GetColor() == 0x444444);

		rectangle->GetOutlineStyle().SetLineWidth(1);
		triangle->GetOutlineStyle().SetLineWidth(2);
		ellipse->GetOutlineStyle().SetLineWidth(3);

		REQUIRE(outlineStyle.GetLineWidth() == nullopt);
		outlineStyle.SetLineWidth(4);
		REQUIRE(*outlineStyle.GetLineWidth() == 4);
	}
}

SCENARIO("test insert group shapes")
{
	shared_ptr<IGroupShape> groupA = make_shared<CGroupShape>();
	shared_ptr<IGroupShape> groupB = make_shared<CGroupShape>();
	shared_ptr<IGroupShape> groupC = make_shared<CGroupShape>();

	REQUIRE_NOTHROW(groupA->InsertShape(groupB));
	REQUIRE_NOTHROW(groupB->InsertShape(groupC));
	REQUIRE_THROWS(groupC->InsertShape(groupA));
}

SCENARIO("test slide")
{
	CSlide slide(100, 120);
	REQUIRE(slide.GetWidth() == 100);
	REQUIRE(slide.GetHeight() == 120);

	REQUIRE(slide.GetShapesCount() == 0);

	shared_ptr<IShape> rectangle = make_shared<CRectangle>(Point{ 10, 10 }, Point{ 20, 20 });
	shared_ptr<IShape> triangle = make_shared<CTriangle>(Point{ 10, 10 }, Point{ 19, 22 }, Point{ 15, 17 });
	shared_ptr<IShape> ellipse = make_shared<CEllipse>(Point{ 10, 10 }, 7, 5);

	slide.InsertShape(rectangle);
	slide.InsertShape(triangle);
	slide.InsertShape(ellipse);

	REQUIRE(slide.GetShapesCount() == 3);
	REQUIRE(slide.GetShapeAtIndex(0) == rectangle);
	REQUIRE(slide.GetShapeAtIndex(1) == triangle);
	REQUIRE(slide.GetShapeAtIndex(2) == ellipse);
	REQUIRE_THROWS(slide.GetShapeAtIndex(3));

	slide.SetBackgroundColor(0x123456);
	REQUIRE(slide.GetBackgroundColor() == 0x123456);

	slide.RemoveShapeAtIndex(1);
	REQUIRE(slide.GetShapeAtIndex(0) == rectangle);
	REQUIRE(slide.GetShapeAtIndex(1) == ellipse);
	REQUIRE_THROWS(slide.GetShapeAtIndex(2));
}