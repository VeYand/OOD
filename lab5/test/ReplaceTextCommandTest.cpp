#include <gtest/gtest.h>
#include "../src/Document/Command/ReplaceTextCommand.h"
#include "../src/Document/Paragraph/CParagraph.h"

class ReplaceTextCommandTestable final : public ReplaceTextCommand
{
public:
	ReplaceTextCommandTestable(
		const std::string &newText,
		size_t position, std::vector<CDocumentItem> &items
	): ReplaceTextCommand(newText, position, items)
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


TEST(ReplaceTextCommandTest, DoExecuteReplaceTextAtPositionSuccess)
{
	std::vector<CDocumentItem> items;
	std::string oldText = "Original text";
	items.emplace_back(std::make_shared<CParagraph>(oldText));

	std::string newText = "Replaced text";
	size_t position = 0;

	ReplaceTextCommandTestable command(newText, position, items);

	command.TestDoExecute();

	auto paragraph = std::dynamic_pointer_cast<CParagraph>(items[position].GetParagraph());
	ASSERT_NE(paragraph, nullptr);
	EXPECT_EQ(paragraph->GetText(), newText);

	command.TestDoUnexecute();

	EXPECT_EQ(paragraph->GetText(), "Original text");
}

TEST(ReplaceTextCommandTest, DoExecuteReplaceTextWithInvalidPositionError)
{
	std::vector<CDocumentItem> items;
	std::string newText = "Text for invalid position";
	size_t invalidPosition = 10;

	ReplaceTextCommandTestable command(newText, invalidPosition, items);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(ReplaceTextCommandTest, DoUnexecuteRestoreOriginalTextSuccess)
{
	std::vector<CDocumentItem> documentItems;
	std::string oldText = "Initial text";
	documentItems.emplace_back(std::make_shared<CParagraph>(oldText));

	std::string newText = "New text";
	size_t position = 0;

	ReplaceTextCommandTestable command(newText, position, documentItems);

	command.TestDoExecute();

	auto paragraph = std::dynamic_pointer_cast<CParagraph>(documentItems[position].GetParagraph());
	ASSERT_NE(paragraph, nullptr);
	EXPECT_EQ(paragraph->GetText(), newText);

	command.TestDoUnexecute();

	EXPECT_EQ(paragraph->GetText(), "Initial text");
}
