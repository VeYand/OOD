#ifndef COMPOUNDCOMMAND_H
#define COMPOUNDCOMMAND_H
#include <vector>

#include "ICommand.h"

class CompoundCommand final : public ICommand
{
public:
	void Execute() override;

	void Unexecute() override;

private:
	std::vector<ICommand> m_commands;
};

#endif //COMPOUNDCOMMAND_H
