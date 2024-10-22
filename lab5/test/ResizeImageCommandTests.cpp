#include <gtest/gtest.h>
#include "../src/Document/Command/InsertParagraphCommand.h"
#include "../src/Document/Command/ReplaceTextCommand.h"
#include "../src/Document/Command/InsertImageCommand.h"
#include "../src/Document/CDocument.h"

const std::string IMAGE_PATH = "dog1.jpg";

class ResizeImageCommandTestable final : public ResizeImageCommand
{
public:
	ResizeImageCommandTestable(
		const size_t position,
		const unsigned width,
		const unsigned height,
		std::vector<CDocumentItem> &items
	): ResizeImageCommand(position, width, height, items)
	{
	}

	void TestDoExecute()
	{
		DoExecute();
	}

	void TestDoUnexecute()
	{
		DoUnexecute();
	}
};

TEST(ResizeImageCommandTests, ExecuteResizesImageSuccess)
{
	std::vector<CDocumentItem> items;
	auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
	items.emplace_back(image);

	ResizeImageCommandTestable command(0, 150, 300, items);

	EXPECT_NO_THROW(command.TestDoExecute());

	ASSERT_EQ(image->GetHeight(), 300);
	ASSERT_EQ(image->GetWidth(), 150);
}

TEST(ResizeImageCommandTests, ExecuteThrowsOnInvalidPositionError)
{
	std::vector<CDocumentItem> items;
	auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
	items.emplace_back(image);

	ResizeImageCommandTestable command(1, 300, 150, items);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(ResizeImageCommandTests, ExecuteThrowsWhenNoImageAtPositionError)
{
	std::vector<CDocumentItem> items;

	ResizeImageCommandTestable command(0, 150, 300, items);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(ResizeImageCommandTests, UnexecuteResizesBackToOriginalSizeSuccess)
{
	std::vector<CDocumentItem> items;
	auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
	items.emplace_back(image);

	ResizeImageCommandTestable command(0, 150, 300, items);

	command.TestDoExecute();
	ASSERT_EQ(image->GetWidth(), 150);
	ASSERT_EQ(image->GetHeight(), 300);

	command.TestDoUnexecute();

	ASSERT_EQ(image->GetWidth(), 100);
	ASSERT_EQ(image->GetHeight(), 200);
}

TEST(ResizeImageCommandTests, UnexecuteThrowsOnInvalidPositionError)
{
	std::vector<CDocumentItem> items;
	auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
	items.emplace_back(image);

	ResizeImageCommandTestable command(1, 150, 300, items);

	EXPECT_THROW(command.TestDoUnexecute(), std::invalid_argument);
}
