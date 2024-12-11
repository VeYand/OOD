#include "MenuFP.h"
#include "Robot.h"

using namespace std;

void CreateMacroCommand(CMenuFP &menu)
{
	std::string name, description;
	std::vector<std::string> commandNames;

	std::cout << "Enter command name: " << std::endl;
	std::getline(std::cin, name);

	std::cout << "Enter command description: " << std::endl;
	std::getline(std::cin, description);

	std::cout << "Type commands to add them to the macro, \"end_macro\" to finish" << std::endl;

	std::string command;
	while (true)
	{
		std::cout << "> ";
		std::getline(std::cin, command);
		if (command == "end_macro")
		{
			break;
		}


		if (menu.IsCommandExists(command))
		{
			commandNames.push_back(command);
			std::cout << "Command \"" << command << "\" added to macro" << std::endl;
		}
		else
		{
			std::cout << "Unknown command" << std::endl;
		}
	}

	menu.AddMacroCommand(name, description, commandNames);
	std::cout << "Macro \"" << name << "\" created" << std::endl;
}

void TestMenuWithFunctionalCommandPattern()
{
	Robot robot;
	CMenuFP menu;

	menu.AddCommand("on", "Turns the Robot on",
	                [ObjectPtr = &robot] { ObjectPtr->TurnOn(); });
	menu.AddCommand("off", "Turns the Robot off",
	                [ObjectPtr = &robot] { ObjectPtr->TurnOff(); });
	menu.AddCommand("north", "Makes the Robot walk north",
	                [ObjectPtr = &robot] { ObjectPtr->Walk(WalkDirection::North); });
	menu.AddCommand("south", "Makes the Robot walk south",
	                [ObjectPtr = &robot] { ObjectPtr->Walk(WalkDirection::South); });
	menu.AddCommand("west", "Makes the Robot walk west",
	                [ObjectPtr = &robot] { ObjectPtr->Walk(WalkDirection::West); });
	menu.AddCommand("east", "Makes the Robot walk east",
	                [ObjectPtr = &robot] { ObjectPtr->Walk(WalkDirection::East); });
	menu.AddCommand("stop", "Stops the Robot",
	                [ObjectPtr = &robot] { ObjectPtr->Stop(); });
	menu.AddCommand("patrol", "Patrol the territory",
	                CMenuFP::CreateMacroCommand<vector<CMenuFP::Command> >({
		                [ObjectPtr = &robot] { ObjectPtr->TurnOn(); },
		                [ObjectPtr = &robot] { ObjectPtr->Walk(WalkDirection::North); },
		                [ObjectPtr = &robot] { ObjectPtr->Walk(WalkDirection::South); },
		                [ObjectPtr = &robot] { ObjectPtr->Walk(WalkDirection::West); },
		                [ObjectPtr = &robot] { ObjectPtr->Walk(WalkDirection::East); },
		                [ObjectPtr = &robot] { ObjectPtr->TurnOff(); }
	                }));
	menu.AddCommand("begin_macro", "Start recording a new macro", [&] {
		CreateMacroCommand(menu);
	});
	menu.AddCommand("help", "Show instructions",
	                [ObjectPtr = &menu] { ObjectPtr->ShowInstructions(); });
	menu.AddCommand("exit", "Exit from this menu",
	                [ObjectPtr = &menu] { ObjectPtr->Exit(); });

	menu.Run();
}

int main()
{
	TestMenuWithFunctionalCommandPattern();

	return 0;
}
