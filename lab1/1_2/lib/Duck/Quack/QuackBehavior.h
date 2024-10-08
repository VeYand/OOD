#ifndef QUACKBEHAVIOR_H
#define QUACKBEHAVIOR_H

#include "IQuackBehavior.h"
#include <iostream>

class QuackBehavior final : public IQuackBehavior
{
public:
	void Quack() override
	{
		std::cout << "Quack Quack!!!" << std::endl;
	}
};

#endif // QUACKBEHAVIOR_H
