#include <memory>
#include "CommandHandler.h"
#include "multi_gumball_machine/CMultiGumballMachine.h"

int main()
{
	auto machine = std::make_unique<multi_gumball_machine::CMultiGumballMachine>(0);
	CommandHandler handler(std::move(machine));
	handler.Run();

	return 0;
}
