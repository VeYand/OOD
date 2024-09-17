#ifndef RUBBERDUCK_H
#define RUBBERDUCK_H

#include "Duck.h"
#include "Fly/FlyNoWay.h"
#include "Quack/SqueakBehavior.h"
#include "Dance/NoDanceBehavior.h"
#include <iostream>
#include "QuackPolicy/QuackAfterEvenFlights.h"

class RubberDuck final : public Duck
{
public:
	RubberDuck()
		: Duck(
			std::make_unique<FlyNoWay>(),
			std::make_unique<SqueakBehavior>(),
			std::make_unique<NoDanceBehavior>(),
			std::make_unique<QuackAfterEvenFlights>()
			)
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};

#endif // RUBBERDUCK_H