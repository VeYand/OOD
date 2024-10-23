#pragma once
#include "ICommand.h"
#include "Robot.h"
#include <vector>
#include <memory>


template<typename Commands>
CMenuFP::Command CreateMacroCommand(Commands &&commands)
{
	return [=] {
		for (auto &command: commands)
		{
			command();
		}
	};
}

class BeginMacroCommand
{
public:
	explicit BeginMacroCommand(CMenuFP &menu)
		: m_menu(menu)
	{
	}

	void Start() const
	{
		std::string name, description;
		std::vector<CMenuFP::Command> commands;

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

			auto it = std::ranges::find_if(m_menu.m_items,
			                               [&](const CMenuFP::Item &item) {
				                               return item.shortcut == command;
			                               });
			if (it != m_menu.m_items.end())
			{
				commands.push_back(it->command);
				std::cout << "Command \"" << command << "\" added to macro" << std::endl;
			}
			else
			{
				std::cout << "Unknown command" << std::endl;
			}
		}

		m_menu.AddItem(name, description, CreateMacroCommand(std::move(commands)));
		std::cout << "Macro \"" << name << "\" created" << std::endl;
	}

private:
	CMenuFP &m_menu;
};

class CTurnOnCommand : public ICommand
{
public:
	CTurnOnCommand(Robot &robot)
		: m_robot(robot)
	{
	}

	void Execute() override
	{
		m_robot.TurnOn();
	}

private:
	Robot &m_robot;
};

class CTurnOffCommand : public ICommand
{
public:
	CTurnOffCommand(Robot &robot)
		: m_robot(robot)
	{
	}

	void Execute() override
	{
		m_robot.TurnOff();
	}

private:
	Robot &m_robot;
};

class CWalkCommand : public ICommand
{
public:
	CWalkCommand(Robot &robot, WalkDirection direction)
		: m_robot(robot)
		  , m_direction(direction)
	{
	}

	void Execute() override
	{
		m_robot.Walk(m_direction);
	}

private:
	Robot &m_robot;
	WalkDirection m_direction;
};

class CStopCommand : public ICommand
{
public:
	CStopCommand(Robot &robot)
		: m_robot(robot)
	{
	}

	void Execute() override
	{
		m_robot.Stop();
	}

private:
	Robot &m_robot;
};

class CMacroCommand : public ICommand
{
public:
	void Execute() override
	{
		for (auto &cmd: m_commands)
		{
			cmd->Execute();
		}
	}

	void AddCommand(std::unique_ptr<ICommand> &&cmd)
	{
		m_commands.push_back(std::move(cmd));
	}

private:
	std::vector<std::unique_ptr<ICommand> > m_commands;
};
