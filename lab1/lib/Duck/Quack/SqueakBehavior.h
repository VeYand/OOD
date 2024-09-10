#ifndef SQUEAKBEHAVIOR_H
#define SQUEAKBEHAVIOR_H

#include "IQuakBehavior.h"
#include <iostream>

class SqueakBehavior final : public IQuackBehavior
{
public:
	void Quack() override
	{
		std::cout << "Squeek!!!" << std::endl;
	}
};

#endif // SQUEAKBEHAVIOR_H
