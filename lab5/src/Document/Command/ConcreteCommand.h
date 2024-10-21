#ifndef CONCRETECOMMAND_H
#define CONCRETECOMMAND_H
#include "AbstractCommand.h"

class ConcreteCommand final : public AbstractCommand
{
public:
	ConcreteCommand() = default;

	void DoExecute() override
	{
	}

	void DoUnexecute() override
	{
	}
};

#endif //CONCRETECOMMAND_H
