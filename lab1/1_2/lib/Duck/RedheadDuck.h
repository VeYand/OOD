#ifndef REDHEADDUCK_H
#define REDHEADDUCK_H

#include "Duck.h"
#include "Dance/DanceMinuetBehavior.h"
#include "Fly/FlyWithWings.h"
#include "Quack/QuackBehavior.h"
#include "QuackPolicy/QuackBeforeOddFlights.h"
#include <memory>

class RedheadDuck final : public Duck
{
public:
	RedheadDuck()
		: Duck(
			std::make_unique<FlyWithWings>(),
			std::make_unique<QuackBehavior>(),
			std::make_unique<DanceMinuetBehavior>(),
			std::make_unique<QuackBeforeOddFlights>()
			)
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};

#endif // REDHEADDUCK_H