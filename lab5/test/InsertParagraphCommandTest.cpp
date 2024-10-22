#include <gtest/gtest.h>
#include "../src/Document/Command/InsertParagraphCommand.h"

class InsertParagraphCommandTestable final : public InsertParagraphCommand
{
public:
	InsertParagraphCommandTestable(
		const std::string &text,
		const std::optional<size_t> position,
		std::vector<CDocumentItem> &items
	): InsertParagraphCommand(text, position, items)
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

TEST(InsertParagraphCommandTest, InsertAtEndSuccess)
{
	std::vector<CDocumentItem> items;
	std::string text = "New paragraph text";

	InsertParagraphCommandTestable command(text, std::nullopt, items);

	command.TestDoExecute();

	ASSERT_EQ(items.size(), 1);

	auto paragraph = std::dynamic_pointer_cast<CParagraph>(items[0].GetParagraph());
	ASSERT_NE(paragraph, nullptr);
	EXPECT_EQ(paragraph->GetText(), text);

	command.TestDoUnexecute();

	EXPECT_TRUE(items.empty());
}

TEST(InsertParagraphCommandTest, InsertAtPositionSuccess)
{
	std::string text = "Existing paragraph";
	auto paragraph = std::make_shared<CParagraph>(text);
	CDocumentItem item(paragraph);
	std::vector<CDocumentItem> items = {item};

	std::string textInserted = "Inserted paragraph";
	size_t position = 0;

	InsertParagraphCommandTestable command(textInserted, position, items);

	command.TestDoExecute();

	ASSERT_EQ(items.size(), 2);

	auto paragraph1 = std::dynamic_pointer_cast<CParagraph>(items[position].GetParagraph());
	ASSERT_NE(paragraph1, nullptr);
	EXPECT_EQ(paragraph1->GetText(), textInserted);

	command.TestDoUnexecute();

	ASSERT_EQ(items.size(), 1);
	EXPECT_EQ(items[0].GetParagraph()->GetText(), "Existing paragraph");
}

TEST(InsertParagraphCommandTest, InsertAtInvalidPositionError)
{
	std::vector<CDocumentItem> items;
	std::string text = "Text for invalid position";
	size_t invalidPosition = 10;

	InsertParagraphCommandTestable command(text, invalidPosition, items);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
	EXPECT_TRUE(items.empty());
}
