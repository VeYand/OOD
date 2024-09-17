#ifndef IQUACKPOLICY_H
#define IQUACKPOLICY_H

struct IQuackPolicy
{
	virtual ~IQuackPolicy() = default;

	[[nodiscard]] virtual bool ShouldQuack(int flightCount, bool isAfterFlight) const = 0;
};

#endif //IQUACKPOLICY_H
