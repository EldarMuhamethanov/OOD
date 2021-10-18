#include "CParagraph.h"

using namespace std;


CParagraph::CParagraph(std::string const& text)
	: m_text(text)
{}
string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const string& text)
{
	m_text = text;
}