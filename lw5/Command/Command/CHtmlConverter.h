#pragma once
#include "IDocument.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <map>

class CHtmlConverter
{
public:
	CHtmlConverter() {};

	static void PrintDocument(const IDocument& document, std::ostream& out);
private:
	static std::string ConvertTitle(std::string title);
	static std::string ConvertParagraph(const IParagraph& paragraph);
	static std::string ConvertImage(const IImage& image);

	static std::regex GetSymbolToHtmlRegex(std::map<std::string, std::string> const& htmlToSymbolMap);
	static const std::string HtmlSymbolEncode(std::string const& html);
};

