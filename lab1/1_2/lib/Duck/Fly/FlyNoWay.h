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

	[[nodiscard]] int GetNextFlightCount() const override
	{
		return 0;
	}
};

#endif // FLYNOWAY_H