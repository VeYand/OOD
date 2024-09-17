#ifndef QUACKAFTEREVENFLIGHTS_H
#define QUACKAFTEREVENFLIGHTS_H
#include "IQuackPolicy.h"

class QuackAfterEvenFlights final : public IQuackPolicy
{
public:
	[[nodiscard]] bool ShouldQuack(const int flightCount, const bool isAfterFlight) const override
	{
		return isAfterFlight && flightCount % 2 == 0;
	}
};

#endif //QUACKAFTEREVENFLIGHTS_H
