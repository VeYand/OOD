#include <gtest/gtest.h>
#include "../src/Document/Command/SetTitleCommand.h"

class SetTitleCommandTestable final : public SetTitleCommand
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
