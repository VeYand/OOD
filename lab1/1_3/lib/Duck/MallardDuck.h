#ifndef MALLARDDUCK_H
#define MALLARDDUCK_H

#include "Duck.h"
#include "Fly/FlyBehavior.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceBehavior.h"

class MallardDuck final : public Duck
{
public:
	MallardDuck()
		: Duck(
			CreateFlyWithWingsBehavior(),
			CreateQuackBehavior(),
			CreateDanceWaltzBehavior()
			)
	{
	}

	void Display() const override
	{
		std::cout << "I'm a mallard duck" << std::endl;
	}
};

#endif // MALLARDDUCK_H