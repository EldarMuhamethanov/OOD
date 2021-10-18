#include "CHtmlConverter.h"


using namespace std;

regex CHtmlConverter::GetSymbolToHtmlRegex(map<string, string> const& htmlToSymbolMap)
{
	string htmlRegexString;
	for (auto& html : htmlToSymbolMap)
	{
		htmlRegexString += "(" + html.first + ")" + "|";
	}
	if (htmlRegexString.size() > 0)
		htmlRegexString.pop_back();
	regex htmlRegex(htmlRegexString);
	return htmlRegex;
}

const string CHtmlConverter::HtmlSymbolEncode(string const& html)
{
	string result;
	static const map<string, string> htmlToSymbolMap{
		{"\"", "&quot;"},
		{"'", "&apos;"},
		{"<", "&lt;"},
		{">", "&gt;"},
		{"&", "&amp;"}
	};
	regex htmlRegex = GetSymbolToHtmlRegex(htmlToSymbolMap);

	const vector<smatch> matches{
		sregex_iterator{html.begin(), html.end(), htmlRegex},
		sregex_iterator{}
	};

	if (matches.size() == 0)
		return html;

	for (smatch const& match : matches)
	{
		string prefix = match.prefix();
		result += prefix + htmlToSymbolMap.at(match[0]);
	}
	result += matches.back().suffix();

	return result;
}

void CHtmlConverter::PrintDocument(const IDocument& document, ostream& out)
{
	string titleHtml = ConvertTitle(HtmlSymbolEncode(document.GetTitle()));
	out << "<html>" << endl;
	out << titleHtml << endl;
	for (size_t i = 0; i < document.GetItemsCount(); i++)
	{
		CConstDocumentItem item = document.GetItem(i);
		shared_ptr<const IParagraph> paragraph = item.GetParagraph();
		if (paragraph != nullptr)
		{
			out << ConvertParagraph(*paragraph) << endl;
			continue;
		}
		shared_ptr<const IImage> image = item.GetImage();
		if (image != nullptr)
		{
			out << ConvertImage(*image) << endl;
		}
	}
	out << "</html>" << endl;
}

string CHtmlConverter::ConvertTitle(string title)
{
	return "<h1>" + title + "</h1>";;
}
string CHtmlConverter::ConvertParagraph(const IParagraph& paragraph)
{
	return "<p>" + HtmlSymbolEncode(paragraph.GetText()) + "</p>";;
}
string CHtmlConverter::ConvertImage(const IImage& image)
{
	return "<img "
		"src='" + HtmlSymbolEncode(image.GetPath()) + "' "
		"width='" + to_string(image.GetWidth()) + "' "
		"height='" + to_string(image.GetHeight()) + "' "
		"/>";
}