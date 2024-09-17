#ifndef DECOYDUCK_H
#define DECOYDUCK_H

#include "Duck.h"
#include "Dance/NoDanceBehavior.h"
#include "Fly/FlyNoWay.h"
#include "Quack/MuteQuackBehavior.h"
#include "QuackPolicy/QuackAfterEvenFlights.h"
#include <iostream>
#include <memory>

class DecoyDuck final : public Duck
{
public:
	DecoyDuck()
		: Duck(
			std::make_unique<FlyNoWay>(),
			std::make_unique<MuteQuackBehavior>(),
			std::make_unique<NoDanceBehavior>(),
			std::make_unique<QuackAfterEvenFlights>()
			)
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}
};

#endif // DECOYDUCK_H