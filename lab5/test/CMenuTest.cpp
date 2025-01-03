#include <gtest/gtest.h>
#include "../src/Menu/CMenu.h"

TEST(MenuTest, AddItemAndShowInstructions)
{
	CMenu menu;
	menu.AddItem("First", "First command", [](std::istringstream &) {
	});
	menu.AddItem("Second", "Second command", [](std::istringstream &) {
	});

	std::stringstream output;
	std::streambuf *oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

	menu.ShowInstructions();
	std::cout.rdbuf(oldCoutBuffer);

	std::string expectedInstructions = "Commands list:\n  First. First command\n  Second. Second command\n";
	EXPECT_EQ(output.str(), expectedInstructions);
}

TEST(MenuTest, ExecuteCommand)
{
	CMenu menu;
	bool commandExecuted = false;

	menu.AddItem("Test", "Test command", [&](std::istringstream &) {
		commandExecuted = true;
	});

	std::stringstream input("Test\n"), output;
	std::streambuf *oldCinBuffer = std::cin.rdbuf(input.rdbuf());
	std::streambuf *oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

	menu.Run();

	std::cin.rdbuf(oldCinBuffer);
	std::cout.rdbuf(oldCoutBuffer);

	EXPECT_TRUE(commandExecuted);
}

TEST(MenuTest, ExitMenu)
{
	CMenu menu;
	menu.AddItem("Exit", "Exit menu", [&](std::istringstream &) {
		menu.Exit();
	});

	std::stringstream input("Exit\n"), output;
	std::streambuf *oldCinBuffer = std::cin.rdbuf(input.rdbuf());
	std::streambuf *oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

	menu.Run();

	std::cin.rdbuf(oldCinBuffer);
	std::cout.rdbuf(oldCoutBuffer);

	EXPECT_EQ(output.str().find("Commands list"), 0);
}

TEST(MenuTest, UnknownCommand)
{
	CMenu menu;
	menu.AddItem("Test", "Test command", [](std::istringstream &) {
	});

	std::stringstream input("unknown\n"), output;
	std::streambuf *oldCinBuffer = std::cin.rdbuf(input.rdbuf());
	std::streambuf *oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

	menu.Run();

	std::cin.rdbuf(oldCinBuffer);
	std::cout.rdbuf(oldCoutBuffer);

	EXPECT_NE(output.str().find("Unknown command"), std::string::npos);
}

TEST(MenuTest, CommandWithArguments)
{
	CMenu menu;
	int capturedValue = 0;

	menu.AddItem("Set", "Set value", [&](std::istringstream &iss) {
		int value;
		iss >> value;
		capturedValue = value;
	});

	std::stringstream input("Set 42\n"), output;
	std::streambuf *oldCinBuffer = std::cin.rdbuf(input.rdbuf());
	std::streambuf *oldCoutBuffer = std::cout.rdbuf(output.rdbuf());

	menu.Run();

	std::cin.rdbuf(oldCinBuffer);
	std::cout.rdbuf(oldCoutBuffer);

	EXPECT_EQ(capturedValue, 42);
}
