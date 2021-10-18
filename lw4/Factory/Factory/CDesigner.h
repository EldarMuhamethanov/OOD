#pragma once
#include "IShapeFactory.h"
#include "IDesigner.h"

class CDesigner: public IDesigner
{
public:
	CDesigner(IShapeFactory& factory);
	~CDesigner();
	CPictureDraft CreateDraft(std::istream& inputData) override;
private:
	IShapeFactory& m_factory;
};

