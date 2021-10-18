#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Factory/CEllipse.h"
#include "../Factory/CRectangle.h"
#include "../Factory/CRegularPolygon.h"
#include "../Factory/CTriangle.h"
#include "../Factory/CShapeFactory.h"
#include "../Factory/CDesigner.h"
#include "../Factory/CPainter.h"
#include "../Factory/CPictureDraft.h"
#include "../Factory/CCanvas.h"


using namespace std;


void CheckEllipse(CEllipse& ellipse, Point center, double horizontalR, double verticalRadius, Color color)
{
	REQUIRE(ellipse.GetHorizontalRadius() == horizontalR);
	REQUIRE(ellipse.GetVerticalRadius() == verticalRadius);

	REQUIRE(ellipse.GetCenter().x == center.x);
	REQUIRE(ellipse.GetCenter().y == center.y);

	REQUIRE(ellipse.GetColor() == color);
}

void CheckRectangle(CRectangle& rect, Point leftTop, Point bottomRight, Color color)
{
	REQUIRE(rect.GetLeftTop().x == leftTop.x);
	REQUIRE(rect.GetLeftTop().y == leftTop.y);

	REQUIRE(rect.GetRightBottom().x == bottomRight.x);
	REQUIRE(rect.GetRightBottom().y == bottomRight.y);

	REQUIRE(rect.GetColor() == color);
}

void CheckTriangle(CTriangle& triangle, Point v1, Point v2, Point v3, Color color)
{
	REQUIRE(triangle.GetVertex1().x == v1.x);
	REQUIRE(triangle.GetVertex1().y == v1.y);

	REQUIRE(triangle.GetVertex2().x == v2.x);
	REQUIRE(triangle.GetVertex2().y == v2.y);

	REQUIRE(triangle.GetVertex3().x == v3.x);
	REQUIRE(triangle.GetVertex3().y == v3.y);

	REQUIRE(triangle.GetColor() == color);
}

void CheckPolygon(CRegularPolygon& polygon, int vertCount, Point center, double radius, Color color)
{
	REQUIRE(polygon.GetVertexCount() == vertCount);

	REQUIRE(polygon.GetCenter().x == center.x);
	REQUIRE(polygon.GetCenter().y == center.y);

	REQUIRE(polygon.GetRadius() == radius);

	REQUIRE(polygon.GetColor() == color);
}

void PrintToCanvas(ostream& out, CPictureDraft& draft)
{
	CCanvas canvas(out);
	CPainter painter;
	painter.DrawPicture(draft, canvas);
}


SCENARIO("test Shapes")
{
	CEllipse ellipse(
		{ 10, 12 },
		15,
		20,
		Color::Green
	);
	CheckEllipse(
		ellipse,
		{ 10 , 12 },
		15,
		20,
		Color::Green
	);


	CTriangle triangle(
		{ 10, 10 },
		{ 12, 15 },
		{ 10, 15 },
		Color::Blue
	);
	CheckTriangle(
		triangle,
		{ 10, 10 },
		{ 12, 15 },
		{ 10, 15 },
		Color::Blue
	);
	

	CRectangle rect(
		{ 10, 12 },
		{ 15, 16 },
		Color::Pink
	);
	CheckRectangle(
		rect,
		{ 10, 12 },
		{ 15, 16 },
		Color::Pink
	);
	

	CRegularPolygon regular(
		6,
		{15, 16},
		5,
		Color::Green
	);
	CheckPolygon(
		regular,
		6,
		{ 15, 16 },
		5,
		Color::Green
	);
}

SCENARIO("tests Factory")
{
	CShapeFactory factory;

	unique_ptr<IShape> shape1 = factory.CreateShape("rectangle red 10 10 15 15");
	CRectangle* rect = dynamic_cast<CRectangle*>(shape1.get());
	REQUIRE(rect != nullptr);
	CheckRectangle(
		*rect,
		{10, 10},
		{15, 15},
		Color::Red
	);

	unique_ptr<IShape> shape2 = factory.CreateShape("triangle green 5 5 7 10 5 10");
	CTriangle* triangle = dynamic_cast<CTriangle*>(shape2.get());
	REQUIRE(triangle != nullptr);
	CheckTriangle(
		*triangle,
		{ 5, 5 },
		{ 7, 10 },
		{ 5, 10 },
		Color::Green
	);

	unique_ptr<IShape> shape3 = factory.CreateShape("ellipse pink 10 10 5 8");
	CEllipse* ellipse = dynamic_cast<CEllipse*>(shape3.get());
	REQUIRE(ellipse != nullptr);
	CheckEllipse(
		*ellipse,
		{ 10, 10 },
		5,
		8,
		Color::Pink
	);

	unique_ptr<IShape> shape4 = factory.CreateShape("polygon black 6 15 15 5");
	CRegularPolygon* polygon = dynamic_cast<CRegularPolygon*>(shape4.get());
	REQUIRE(polygon != nullptr);
	CheckPolygon(
		*polygon,
		6,
		{ 15, 15 },
		5,
		Color::Black
	);

	WHEN("not enough params")
	{
		REQUIRE_THROWS(factory.CreateShape("polygon black 6 15 15"));
	}
	WHEN("unknown shape name")
	{
		REQUIRE_THROWS(factory.CreateShape("circle black 6 15 15"));
	}
	WHEN("unknown color")
	{
		REQUIRE_THROWS(factory.CreateShape("triangle white 5 5 7 10 5 10"));
	}
	WHEN("invalid polygon with 2 vertex")
	{
		REQUIRE_THROWS(factory.CreateShape("polygon black 2 15 15 5"));
	}
	WHEN("invalid triangle")
	{
		REQUIRE_THROWS(factory.CreateShape("triangle green 5 5 10 10 7 7"));
	}
	WHEN("shape with invalid params")
	{
		REQUIRE_THROWS(factory.CreateShape("rectangle black 10 p 15 15"));
	}
	WHEN("shape with negative params")
	{
		REQUIRE_THROWS(factory.CreateShape("rectangle black 10 -10 15 15"));
	}
}

SCENARIO("Designer and PictureDraft tests And when Painter And Canvas")
{
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);

	string input = "rectangle red 10 10 15 15\n"
		"triangle green 5 5 7 10 5 10\n"
		"ellipse pink 10 10 5 8\n"
		"circle black 6 15 15\n"
		"polygon black 6 15 15 5\n"
		"polygon black 6 15 15\n"
		"polygon black 2 15 15 5\n";
	istringstream in(input);

	CPictureDraft draft = designer.CreateDraft(in);

	REQUIRE(draft.GetShapeCount() == 4);
	CRectangle* rect = dynamic_cast<CRectangle*>(draft.GetShape(0).get());
	REQUIRE(rect != nullptr);
	CheckRectangle(
		*rect,
		{ 10, 10 },
		{ 15, 15 },
		Color::Red
	);
	CTriangle* triangle = dynamic_cast<CTriangle*>(draft.GetShape(1).get());
	REQUIRE(triangle != nullptr);
	CheckTriangle(
		*triangle,
		{ 5, 5 },
		{ 7, 10 },
		{ 5, 10 },
		Color::Green
	);
	CEllipse* ellipse = dynamic_cast<CEllipse*>(draft.GetShape(2).get());
	REQUIRE(ellipse != nullptr);
	CheckEllipse(
		*ellipse,
		{ 10, 10 },
		5,
		8,
		Color::Pink
	);
	CRegularPolygon* polygon = dynamic_cast<CRegularPolygon*>(draft.GetShape(3).get());
	REQUIRE(polygon != nullptr);
	CheckPolygon(
		*polygon,
		6,
		{ 15, 15 },
		5,
		Color::Black
	);

	WHEN("Test painter And Canvas")
	{
		string result = "<svg xmlns='http://www.w3.org/2000/svg' width='1000' height='1000' viewPort='0 0 1000 1000'>\n"
			"<line x1 = '10' y1 = '10' x2 = '15' y2 = '10' stroke = 'red' stroke-width = '5'/>\n"
			"<line x1 = '15' y1 = '10' x2 = '15' y2 = '15' stroke = 'red' stroke-width = '5'/>\n"
			"<line x1 = '10' y1 = '10' x2 = '10' y2 = '15' stroke = 'red' stroke-width = '5'/>\n"
			"<line x1 = '10' y1 = '15' x2 = '15' y2 = '15' stroke = 'red' stroke-width = '5'/>\n"
			"<line x1 = '5' y1 = '5' x2 = '7' y2 = '10' stroke = 'green' stroke-width = '5'/>\n"
			"<line x1 = '7' y1 = '10' x2 = '5' y2 = '10' stroke = 'green' stroke-width = '5'/>\n"
			"<line x1 = '5' y1 = '5' x2 = '5' y2 = '10' stroke = 'green' stroke-width = '5'/>\n"
			"<ellipse rx = '5' ry = '8' cx = '10' cy = '10' stroke = 'pink' stroke-width = '5' fill = 'transparent'/>\n"
			"<line x1 = '19.3288' y1 = '17.5023' x2 = '15' y2 = '20' stroke = 'black' stroke-width = '5'/>\n"
			"<line x1 = '19.3328' y1 = '12.5046' x2 = '19.3288' y2 = '17.5023' stroke = 'black' stroke-width = '5'/>\n"
			"<line x1 = '15.008' y1 = '10' x2 = '19.3328' y2 = '12.5046' stroke = 'black' stroke-width = '5'/>\n"
			"<line x1 = '10.6752' y1 = '12.4908' x2 = '15.008' y2 = '10' stroke = 'black' stroke-width = '5'/>\n"
			"<line x1 = '10.6633' y1 = '17.4885' x2 = '10.6752' y2 = '12.4908' stroke = 'black' stroke-width = '5'/>\n"
			"<line x1 = '15' y1 = '20' x2 = '10.6633' y2 = '17.4885' stroke = 'black' stroke-width = '5'/>\n"
			"</svg>\n";
		string out;
		ostringstream outStrm(out);
		PrintToCanvas(outStrm, draft);

		REQUIRE(outStrm.str() == result);
	}
}