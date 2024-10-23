#include "MenuFP.h"
#include "Commands.h"

using namespace std;

void TestMenuWithFunctionalCommandPattern()
{
	Robot robot;
	CMenuFP menu;

	menu.AddItem("on", "Turns the Robot on",
	             bind(&Robot::TurnOn, &robot));
	menu.AddItem("off", "Turns the Robot off",
	             bind(&Robot::TurnOff, &robot));
	menu.AddItem("north", "Makes the Robot walk north",
	             bind(&Robot::Walk, &robot, WalkDirection::North));
	menu.AddItem("south", "Makes the Robot walk south",
	             bind(&Robot::Walk, &robot, WalkDirection::South));
	menu.AddItem("west", "Makes the Robot walk west",
	             bind(&Robot::Walk, &robot, WalkDirection::West));
	menu.AddItem("east", "Makes the Robot walk east",
	             bind(&Robot::Walk, &robot, WalkDirection::East));
	menu.AddItem("stop", "Stops the Robot",
	             bind(&Robot::Stop, &robot));
	menu.AddItem("patrol", "Patrol the territory",
	             CreateMacroCommand<vector<CMenuFP::Command> >({
		             bind(&Robot::TurnOn, &robot),
		             bind(&Robot::Walk, &robot, WalkDirection::North),
		             bind(&Robot::Walk, &robot, WalkDirection::South),
		             bind(&Robot::Walk, &robot, WalkDirection::West),
		             bind(&Robot::Walk, &robot, WalkDirection::East),
		             bind(&Robot::TurnOff, &robot)
	             }));

	menu.AddItem("begin_macro", "Start recording a new macro", [&] {
		const BeginMacroCommand beginMacroCommand(menu);
		beginMacroCommand.Start();
	});

	menu.AddItem("help", "Show instructions",
	             bind(&CMenuFP::ShowInstructions, &menu));
	menu.AddItem("exit", "Exit from this menu",
	             bind(&CMenuFP::Exit, &menu));

	menu.Run();
}

int main()
{
	TestMenuWithFunctionalCommandPattern();

	return 0;
}
