#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include "Duck.h"
#include "Dance/DanceWaltzBehavior.h"
#include "Fly/FlyWithWings.h"
#include "Quack/QuackBehavior.h"

class MallardDuck final : public Duck
{
public:
	MallardDuck()
		: Duck(
			std::make_unique<FlyWithWings>(),
			std::make_unique<QuackBehavior>(),
			std::make_unique<DanceWaltzBehavior>()
			)
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};

#endif // MALLARDDUCK_H