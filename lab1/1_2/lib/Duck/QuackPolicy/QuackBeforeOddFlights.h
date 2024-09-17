#ifndef QUACKBEFOREODDFLIGHTS_H
#define QUACKBEFOREODDFLIGHTS_H
#include "IQuackPolicy.h"

class QuackBeforeOddFlights final : public IQuackPolicy
{
public:
	[[nodiscard]] bool ShouldQuack(const int flightCount, const bool isAfterFlight) const override
	{
		return !isAfterFlight && flightCount % 2 != 0;
	}
};

#endif //QUACKBEFOREODDFLIGHTS_H
