#ifndef FLYNOWAY_H
#define FLYNOWAY_H

#include "IFlyBehavior.h"

class FlyNoWay final : public IFlyBehavior
{
public:
	void Fly() override
	{
	}

	[[nodiscard]] int GetFlightCount() const override
	{
		return 0;
	}

	[[nodiscard]] bool CanFly() const override
	{
		return false;
	}
};

#endif // FLYNOWAY_H