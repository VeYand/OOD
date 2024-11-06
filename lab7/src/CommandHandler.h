#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <sstream>
#include "Menu/CMenu.h"

class CommandHandler
{
public:
	CommandHandler()
	{
		m_menu.AddItem(
			"IsertShape",
			"Usage: InsertShape <type> ...",
			[&](std::istringstream &params) { InsertShape(params); }
		);

		m_menu.AddItem(
			"Draw",
			"...",
			[&](std::istringstream &params) { Draw(params); }
		);


		m_menu.AddItem(
			"Help",
			"...",
			[&](std::istringstream &params) { Help(); }
		);

		m_menu.AddItem(
			"Exit",
			"Usage: Exit. Exits the program.",
			[&](std::istringstream &params) { Exit(); }
		);
	}

	void InsertShape(std::istringstream &params)
	{
		// TODO: Use factory
	}

	void Draw(std::istringstream &params)
	{
		// TODO
	}

	void Help()
	{
		m_menu.ShowInstructions();
	}

	void Exit()
	{
		m_menu.Exit();
	}

	void Run()
	{
		m_menu.Run();
	}

private:
	CMenu m_menu{};
};

#endif //COMMANDHANDLER_H
