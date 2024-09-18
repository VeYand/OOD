#ifndef REDHEADDUCK_H
#define REDHEADDUCK_H

#include "Duck.h"
#include "Fly/FlyBehavior.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceBehavior.h"

class RedheadDuck final : public Duck
{
public:
	RedheadDuck()
		: Duck(
			CreateFlyWithWingsBehavior(),
			CreateQuackBehavior(),
			CreateDanceMinuetBehavior()
			)
	{
	}

	void Display() const override
	{
		std::cout << "I'm a redhead duck" << std::endl;
	}
};

#endif //REDHEADDUCK_H
