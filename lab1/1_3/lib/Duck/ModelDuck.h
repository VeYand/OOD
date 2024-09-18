#ifndef MODELDUCK_H
#define MODELDUCK_H

#include "Duck.h"
#include "Fly/FlyBehavior.h"
#include "Quack/QuackBehavior.h"
#include "Dance/DanceBehavior.h"

class ModelDuck final : public Duck
{
public:
	ModelDuck()
		: Duck(
			CreateFlyNoWayBehavior(),
			CreateQuackBehavior(),
			CreateNoDanceBehavior()
			)
	{
	}

	void Display() const override
	{
		std::cout << "I'm a model duck" << std::endl;
	}
};


#endif //MODELDUCK_H
