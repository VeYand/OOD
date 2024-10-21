#include <gtest/gtest.h>
#include "../src/Document/Command/InsertParagraphCommand.h"
#include "../src/Document/Command/ReplaceTextCommand.h"
#include "../src/Document/Command/DeleteItemCommand.h"
#include "../src/Document/Command/SetTitleCommand.h"
#include "../src/Document/Command/InsertImageCommand.h"
#include "../src/Document/CDocument.h"

const std::string IMAGE_PATH = "cat1.jpg";

bool AssertDirectoryIsNotEmpty(const std::string &path)
{
	std::filesystem::path dirPath(path);
	if (!exists(dirPath) || !is_directory(dirPath))
	{
		return false;
	}

	return std::any_of(std::filesystem::directory_iterator(dirPath), std::filesystem::directory_iterator{},
	                   [](const std::filesystem::directory_entry &) {
		                   return true;
	                   });
}

std::string GetFirstFileOnDirectory(const std::string &path)
{
	std::filesystem::path dirPath(path);
	if (!exists(dirPath) || !is_directory(dirPath))
	{
		return "";
	}

	for (const auto &entry: std::filesystem::directory_iterator(dirPath))
	{
		if (is_regular_file(entry.status()))
		{
			return entry.path().filename().string();
		}
	}

	return "";
}

bool AssertFilesAreEqual(const std::string &path1, const std::string &path2)
{
	std::ifstream file1(path1, std::ios::binary);
	std::ifstream file2(path2, std::ios::binary);

	if (!file1.is_open() || !file2.is_open())
	{
		return false;
	}

	file1.seekg(0, std::ios::end);
	file2.seekg(0, std::ios::end);

	if (file1.tellg() != file2.tellg())
	{
		return false;
	}

	file1.seekg(0);
	file2.seekg(0);

	return std::equal(std::istreambuf_iterator(file1),
	                  std::istreambuf_iterator<char>(),
	                  std::istreambuf_iterator(file2));
}

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

class ReplaceTextCommandTestable : public ReplaceTextCommand
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

class DeleteItemCommandTestable : public DeleteItemCommand
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

class SetTitleCommandTestable : public SetTitleCommand
{
public:
	SetTitleCommandTestable(
		std::string &title,
		const std::string &newTitle
	): SetTitleCommand(title, newTitle)
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

class InsertImageCommandTestable : public InsertImageCommand
{
public:
	InsertImageCommandTestable(
		const Path &path,
		int width,
		int height,
		std::optional<size_t> position,
		std::vector<CDocumentItem> &items
	): InsertImageCommand(path, width, height, position, items)
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

TEST(SetTitleCommandTest, DoExecuteSetsNewTitleSuccess)
{
	std::string title = "Original Title";
	std::string newTitle = "New Title";

	SetTitleCommandTestable command(title, newTitle);

	command.TestDoExecute();

	EXPECT_EQ(title, "New Title");

	command.TestDoUnexecute();

	EXPECT_EQ(title, "Original Title");
}

TEST(SetTitleCommandTest, DoUnexecuteRevertsToOldTitleSuccess)
{
	std::string title = "Initial Title";
	std::string newTitle = "Updated Title";

	SetTitleCommandTestable command(title, newTitle);

	command.TestDoExecute();

	EXPECT_EQ(title, "Updated Title");

	command.TestDoUnexecute();

	EXPECT_EQ(title, "Initial Title");
}

TEST(SetTitleCommandTest, RepeatedExecuteAndUnexecuteSuccess)
{
	std::string title = "Start Title";
	std::string newTitle = "Changed Title";

	SetTitleCommandTestable command(title, newTitle);

	command.TestDoExecute();
	EXPECT_EQ(title, "Changed Title");

	command.TestDoUnexecute();
	EXPECT_EQ(title, "Start Title");

	command.TestDoExecute();
	EXPECT_EQ(title, "Changed Title");

	command.TestDoUnexecute();
	EXPECT_EQ(title, "Start Title");
}

TEST(SetTitleCommandTest, DoExecuteWithSameTitleSuccess)
{
	std::string title = "Same Title";

	SetTitleCommandTestable command(title, title);

	command.TestDoExecute();

	EXPECT_EQ(title, "Same Title");

	command.TestDoUnexecute();

	EXPECT_EQ(title, "Same Title");
}

TEST(InsertImageCommandTests, ExecuteInsertsImageAtEndSuccess)
{
	std::vector<CDocumentItem> items;
	std::string imagePath = IMAGE_PATH;
	int width = 100;
	int height = 200;

	InsertImageCommandTestable command(imagePath, width, height, std::nullopt, items);

	EXPECT_NO_THROW(command.TestDoExecute());

	ASSERT_EQ(items.size(), 1);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));
}

TEST(InsertImageCommandTests, ExecuteInsertsImageAtPositionSuccess)
{
	std::vector<CDocumentItem> items;
	std::string imagePath = IMAGE_PATH;
	int width = 100;
	int height = 200;

	InsertImageCommandTestable command(imagePath, width, height, 0, items);

	EXPECT_NO_THROW(command.TestDoExecute());

	ASSERT_EQ(items.size(), 1);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));
}

TEST(InsertImageCommandTests, ExecuteThrowsOnInvalidPositionError)
{
	std::vector<CDocumentItem> items;
	std::string imagePath = IMAGE_PATH;
	int width = 100;
	int height = 200;

	InsertImageCommandTestable command(imagePath, width, height, 2, items);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(InsertImageCommandTests, UnexecuteRemovesLastInsertedSuccess)
{
	std::vector<CDocumentItem> items;
	std::string imagePath = IMAGE_PATH;
	int width = 100;
	int height = 200;

	InsertImageCommandTestable command(imagePath, width, height, std::nullopt, items);

	command.TestDoExecute();
	ASSERT_EQ(items.size(), 1);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));

	command.TestDoUnexecute();
	ASSERT_EQ(items.size(), 0);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));
}

TEST(InsertImageCommandTests, UnexecuteRemovesInsertedAtPosition)
{
	std::vector<CDocumentItem> items;
	std::string imagePath = IMAGE_PATH;
	int width = 100;
	int height = 200;

	InsertImageCommandTestable command(imagePath, width, height, 0, items);

	command.TestDoExecute();
	ASSERT_EQ(items.size(), 1);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));

	command.TestDoUnexecute();
	ASSERT_EQ(items.size(), 0);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("temp"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "temp/" + GetFirstFileOnDirectory("temp")));
}
