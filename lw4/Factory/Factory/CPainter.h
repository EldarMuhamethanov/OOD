#pragma once
#include "CPictureDraft.h"
#include "ICanvas.h"

class CPainter
{
public:
	CPainter() {};
	void DrawPicture(CPictureDraft& draft, ICanvas& canvas);
};

