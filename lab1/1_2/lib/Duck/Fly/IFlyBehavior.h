#ifndef LAB01_SIMUDUCK_IFLYBEHAVIOR_H
#define LAB01_SIMUDUCK_IFLYBEHAVIOR_H

struct IFlyBehavior
{
	virtual ~IFlyBehavior() = default;

	virtual void Fly() = 0;

	[[nodiscard]] virtual int GetFlightCount() const = 0;
};

#endif // LAB01_SIMUDUCK_IFLYBEHAVIOR_H
