#include "Document/CDocument.h"
#include "Menu/CMenu.h"
#include <iostream>
#include <format>

int main()
{
	CMenu menu;
	CDocument document;

	menu.AddItem(
		"InsertParagraph",
		"Usage: InsertParagraph <position>|end <text>. Inserts a paragraph into the specified position.",
		[&](std::istringstream &params) {
			std::string positionInput;
			std::string text;

			if (!(params >> positionInput >> text))
			{
				std::cerr << "Invalid arguments." << std::endl;
				return;
			}

			std::optional<size_t> position = std::nullopt;
			if (positionInput != "end")
			{
				try
				{
					position = std::stoi(positionInput);
				}
				catch (std::invalid_argument &)
				{
					std::cerr << "Error: The position must be an uint or 'end'." << std::endl;
					return;
				}
			}

			document.InsertParagraph(text, position);
		}
	);

	menu.AddItem(
		"InsertImage",
		"Usage: InsertImage <position>|end <width> <height> <image-path>. Inserts an image with the specified width and height.",
		[&](std::istringstream &params) {
			std::string positionInput;
			unsigned width;
			unsigned height;
			std::string imagePath;

			if (!(params >> positionInput >> width >> height >> imagePath))
			{
				std::cerr << "Invalid arguments." << std::endl;
				return;
			}

			std::optional<size_t> position = std::nullopt;
			if (positionInput != "end")
			{
				try
				{
					position = std::stoi(positionInput);
				}
				catch (std::invalid_argument &)
				{
					std::cerr << "Error: The position must be an integer or 'end'." << std::endl;;
					return;
				}
			}

			document.InsertImage(imagePath, width, height, position);
		}
	);

	menu.AddItem(
		"SetTitle",
		"Usage: SetTitle <title>. Sets the document title.",
		[&](std::istringstream &params) {
			std::string newTitle;
			params >> newTitle;
			document.SetTitle(newTitle);
		}
	);

	menu.AddItem(
		"List",
		"Usage: List. Displays the title and list of document elements.",
		[&](std::istringstream &params) {
			const auto title = document.GetTitle();
			const auto itemCount = document.GetItemsCount();

			std::cout << "Title: " << title << std::endl;
			for (int i = 0; i < itemCount; ++i)
			{
				auto item = document.GetItem(i);
				auto image = item.GetImage();
				auto paragraph = item.GetParagraph();
				std::string description{};

				if (image != nullptr)
				{
					description = std::format("Image: {} {} {}", image->GetWidth(), image->GetHeight(),
					                          image->GetPath());
				}

				if (paragraph != nullptr)
				{
					description = std::format("Paragraph: {}", paragraph->GetText());
				}

				std::cout << i + 1 << ". " << description << std::endl;
			}
		}
	);

	menu.AddItem(
		"ReplaceText",
		"Usage: ReplaceText <position> <text>. Replaces the text in the paragraph by the specified position.",
		[&](std::istringstream &params) {
			size_t position;
			std::string newText;

			if (!(params >> position >> newText))
			{
				std::cerr << "Invalid arguments." << std::endl;
				return;
			}

			if (newText.empty())
			{
				std::cerr << "Error: text cannot be empty." << std::endl;
				return;
			}

			document.ReplaceText(newText, position);
		}
	);

	menu.AddItem(
		"ResizeImage",
		"Usage: ResizeImage <position> <width> <height>. Resizes the image at the specified position.",
		[&](std::istringstream &params) {
			size_t position;
			unsigned newWidth;
			unsigned newHeight;

			if (!(params >> position >> newWidth >> newHeight))
			{
				std::cerr << "Invalid arguments." << std::endl;
				return;
			}


			document.ResizeImage(position, newWidth, newHeight);
		}
	);

	menu.AddItem(
		"DeleteItem",
		"Usage: DeleteItem <position>. Deletes an item at the specified position.",
		[&](std::istringstream &params) {
			size_t position;
			if (!(params >> position))
			{
				std::cerr << "Invalid arguments." << std::endl;
				return;
			}
			document.DeleteItem(position);
		}
	);

	menu.AddItem(
		"Help",
		"Usage: Help. Shows the available commands.", [&](std::istringstream &params) {
			menu.ShowInstructions();
		}
	);

	menu.AddItem(
		"Undo",
		"Usage: Undo. Cancels the last action.",
		[&](std::istringstream &params) {
			if (!document.CanUndo())
			{
				std::cout << "Cancellation is not possible!" << std::endl;
				return;
			}

			document.Undo();
		}
	);

	menu.AddItem(
		"Redo",
		"Usage: Redo. Repeats the last canceled action.",
		[&](std::istringstream &params) {
			if (!document.CanRedo())
			{
				std::cout << "Repeat is not possible!" << std::endl;
				return;
			}

			document.Redo();
		}
	);

	menu.AddItem(
		"Save",
		"Usage: Save <path>. Saves the document to a file.",
		[&](std::istringstream &params) {
			std::string filePath;
			if (!(params >> filePath))
			{
				std::cerr << "Invalid arguments." << std::endl;
				return;
			}
			document.Save(filePath);
		}
	);

	menu.AddItem(
		"Exit",
		"Usage: Exit. Exits the program.",
		[&](std::istringstream &params) {
			menu.Exit();
		}
	);

	menu.Run();
}
