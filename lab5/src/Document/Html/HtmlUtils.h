#ifndef HTMLUTILS_H
#define HTMLUTILS_H
#include <fstream>
#include <vector>

#include "../CConstDocumentItem.h"

class HtmlUtils
{
public:
	static void CreateHtmlFile(const std::string &title, const std::vector<CConstDocumentItem> &items,
	                           const std::string &filePath)
	{
		std::ofstream output(filePath);
		if (!output.is_open())
		{
			throw std::runtime_error("Unable to open output file");
		}

		output << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n";
		output << "<title>" << HtmlEncode(title) << "</title>\n";
		output << "</head>\n<body>\n";

		for (const auto &item: items)
		{
			auto paragraph = item.GetParagraph();
			auto image = item.GetImage();

			if (paragraph != nullptr)
			{
				output << "<p>" << HtmlEncode(paragraph->GetText()) << "</p>\n";
			}

			if (image != nullptr)
			{
				output << "<img src=\"" << HtmlEncode(image->GetPath()) << "\" "
						<< "width=" << image->GetWidth() << " "
						<< "height=" << image->GetHeight()
						<< " />";
			}
		}

		output << "</body>\n</html>";

		output.close();
	}

private:
	static std::string HtmlEncode(const std::string &text)
	{
		std::string encoded;
		for (const auto ch: text)
		{
			switch (ch)
			{
				case '<': encoded += "&lt;";
					break;
				case '>': encoded += "&gt;";
					break;
				case '"': encoded += "&quot;";
					break;
				case '\'': encoded += "&apos;";
					break;
				case '&': encoded += "&amp;";
					break;
				default: encoded += ch;
					break;
			}
		}
		return encoded;
	}
};

#endif //HTMLUTILS_H
