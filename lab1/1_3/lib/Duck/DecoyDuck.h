#ifndef DECOYDUCK_H
#define DECOYDUCK_H
#include "Duck.h"
#include "Fly/FlyBehavior.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceBehavior.h"

class DecoyDuck final : public Duck
{
public:
	DecoyDuck()
		: Duck(
			CreateFlyNoWayBehavior(),
			CreateMuteQuackBehavior(),
			CreateNoDanceBehavior()
			)
	{
	}

	void Display() const override
	{
		std::cout << "I'm a decoy duck" << std::endl;
	}
};

#endif //DECOYDUCK_H