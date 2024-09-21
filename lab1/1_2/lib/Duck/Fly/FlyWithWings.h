#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H

#include "IFlyBehavior.h"
#include <iostream>

class FlyWithWings final : public IFlyBehavior
{
public:
	void Fly() override
	{
		m_flyAmmount++;
		std::cout << "I'm flying with wings!! Fly ammount: " << m_flyAmmount << std::endl;
	}

	[[nodiscard]] int GetFlightCount() const override
	{
		return m_flyAmmount;
	}

	[[nodiscard]] bool CanFly() const override
	{
		return true;
	}

private:
	int m_flyAmmount = 0;
};

#endif // FLYWITHWINGS_H