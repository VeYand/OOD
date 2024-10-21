#include "Document/CDocument.h"
#include "Menu/CMenu.h"
#include <iostream>
#include <format>

int main()
{
	CMenu menu;
	CDocument document;

	menu.AddItem("InsertParagraph", "123", [&](std::istringstream &params) {
		std::string postition;
		std::string text;

		params >> postition >> text;

		std::optional<size_t> position2 = std::nullopt;
		if (postition != "end")
		{
			position2 = std::stoi(postition);
		}

		document.InsertParagraph(text, position2);
	});

	menu.AddItem("InsertImage", "123", [&](std::istringstream &params) {
		std::string postition;
		unsigned width;
		unsigned height;
		std::string path;


		params >> postition >> width >> height >> path;

		std::optional<size_t> position2 = std::nullopt;
		if (postition != "end")
		{
			position2 = std::stoi(postition);
		}

		document.InsertImage(path, width, height, position2);
	});

	menu.AddItem("SetTitle", "123", [&](std::istringstream &params) {
		std::string newTitle;
		params >> newTitle;
		document.SetTitle(newTitle);
	});

	menu.AddItem("List", "123", [&](std::istringstream &params) {
		const auto title = document.GetTitle();
		const auto itemsCount = document.GetItemsCount();

		std::cout << "Title: " << title << std::endl;
		for (int i = 0; i < itemsCount; ++i)
		{
			auto item = document.GetItem(i);
			auto image = item.GetImage();
			auto paragraph = item.GetParagraph();
			std::string description{};

			if (image != nullptr)
			{
				description = std::format("Image: {} {} {}", image->GetWidth(), image->GetHeight(), image->GetPath());
			}

			if (paragraph != nullptr)
			{
				description = std::format("Paragraph: {}", paragraph->GetText());
			}

			std::cout << i + 1 << ". " << description << std::endl;
		}
	});

	menu.AddItem("ReplaceText", "123", [&](std::istringstream &params) {
		size_t position;
		std::string text;

		params >> position >> text;
		document.ReplaceText(text, position);
	});

	menu.AddItem("ResizeImage", "123", [&](std::istringstream &params) {
		size_t position;
		unsigned width;
		unsigned height;


		params >> position >> width >> height;

		document.ResizeImage(position, width, height);
	});

	menu.AddItem("DeleteItem", "123", [&](std::istringstream &params) {
		size_t postition;
		params >> postition;
		document.DeleteItem(postition);
	});

	menu.AddItem("Help", "123", [&](std::istringstream &params) {
		menu.ShowInstructions();
	});

	menu.AddItem("Undo", "123", [&](std::istringstream &params) {
		const auto canUndo = document.CanUndo();

		if (!canUndo)
		{
			std::cout << "!" << std::endl;
			return;
		}

		document.Undo();
	});

	menu.AddItem("Redo", "123", [&](std::istringstream &params) {
		const auto canRedo = document.CanRedo();

		if (!canRedo)
		{
			std::cout << "!" << std::endl;
			return;
		}

		document.Redo();
	});

	menu.AddItem("Save", "123", [&](std::istringstream &params) {
		std::string path;
		params >> path;
		document.Save(path);
	});

	menu.AddItem("Exit", "123", [&](std::istringstream &params) {
		menu.Exit();
	});


	menu.Run();
}
