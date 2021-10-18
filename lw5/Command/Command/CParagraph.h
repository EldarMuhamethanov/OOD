#pragma once
#include <memory>
#include "IParagraph.h"

class CParagraph :public IParagraph
{
public:
	CParagraph(std::string const& text);
	std::string GetText()const override;
	void SetText(const std::string& text) override;
private:
	std::string m_text;
};

