#ifndef RUBBERDUCK_H
#define RUBBERDUCK_H

#include "Duck.h"
#include "Fly/FlyBehavior.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceBehavior.h"

class RubberDuck final : public Duck
{
public:
	RubberDuck()
		: Duck(
			CreateFlyNoWayBehavior(),
			CreateSqueakBehavior(),
			CreateNoDanceBehavior()
			)
	{
	}

	void Display() const override
	{
		std::cout << "I'm a rubber duck" << std::endl;
	}
};

#endif //RUBBERDUCK_H