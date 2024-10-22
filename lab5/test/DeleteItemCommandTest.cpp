#include <gtest/gtest.h>
#include "../src/Document/Command/DeleteItemCommand.h"
#include "../src/Document/Paragraph/CParagraph.h"

class DeleteItemCommandTestable final : public DeleteItemCommand
{
public:
	DeleteItemCommandTestable(
		size_t position,
		std::vector<CDocumentItem> &items
	): DeleteItemCommand(position, items)
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

TEST(DeleteItemCommandTest, DoExecuteDeleteItemAtSpecifiedPositionSuccess)
{
	std::vector<CDocumentItem> items;
	std::string text1 = "Paragraph 1";
	std::string text2 = "Paragraph 2";
	items.emplace_back(std::make_shared<CParagraph>(text1));
	items.emplace_back(std::make_shared<CParagraph>(text2));

	size_t position = 1;
	DeleteItemCommandTestable command(position, items);

	command.TestDoExecute();

	ASSERT_EQ(items.size(), 1);
	EXPECT_EQ(items[0].GetParagraph()->GetText(), "Paragraph 1");

	command.TestDoUnexecute();

	ASSERT_EQ(items.size(), 2);
	EXPECT_EQ(items[1].GetParagraph()->GetText(), "Paragraph 2");
}

TEST(DeleteItemCommandTest, DoExecuteDeleteItemWithInvalidPositionError)
{
	std::vector<CDocumentItem> items;
	std::string text = "Paragraph 1";
	items.emplace_back(std::make_shared<CParagraph>(text));

	size_t invalidPosition = 5;
	DeleteItemCommandTestable command(invalidPosition, items);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(DeleteItemCommandTest, DoExecuteDeleteOnlyItemSuccess)
{
	std::vector<CDocumentItem> items;
	std::string text = "Only paragraph";
	items.emplace_back(std::make_shared<CParagraph>(text));

	size_t position = 0;
	DeleteItemCommandTestable command(position, items);

	command.TestDoExecute();

	EXPECT_TRUE(items.empty());

	command.TestDoUnexecute();

	ASSERT_EQ(items.size(), 1);
	EXPECT_EQ(items[0].GetParagraph()->GetText(), "Only paragraph");
}


TEST(DeleteItemCommandTest, DoExecuteDeleteItemAtPositionZeroSuccess)
{
	std::vector<CDocumentItem> items;
	std::string text1 = "Paragraph 1";
	std::string text2 = "Paragraph 2";
	std::string text3 = "Paragraph 3";
	items.emplace_back(std::make_shared<CParagraph>(text1));
	items.emplace_back(std::make_shared<CParagraph>(text2));
	items.emplace_back(std::make_shared<CParagraph>(text3));

	size_t position = 0;
	DeleteItemCommandTestable command(position, items);

	command.TestDoExecute();

	ASSERT_EQ(items.size(), 2);
	EXPECT_EQ(items[0].GetParagraph()->GetText(), "Paragraph 2");

	command.TestDoUnexecute();

	ASSERT_EQ(items.size(), 3);
	EXPECT_EQ(items[0].GetParagraph()->GetText(), "Paragraph 1");
}

TEST(DeleteItemCommandTest, DoUnexecuteOnEmptyListError)
{
	std::vector<CDocumentItem> items;

	size_t position = 0;
	DeleteItemCommandTestable command(position, items);

	EXPECT_NO_THROW(command.TestDoUnexecute());

	EXPECT_TRUE(items.empty());
}
