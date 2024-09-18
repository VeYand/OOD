#ifndef FLYBEHAVIOR_H
#define FLYBEHAVIOR_H

#include <iostream>
#include <functional>

using FlyBehavior = std::function<void()>;

inline FlyBehavior CreateFlyWithWingsBehavior()
{
	int flightAmmount = 0;
	return [flightAmmount]() mutable {
		flightAmmount++;
		std::cout << "I'm flying with wings!! Fly ammount: " << flightAmmount << std::endl;
	};
}

inline FlyBehavior CreateFlyNoWayBehavior()
{
	return []() {};
}

#endif // FLYBEHAVIOR_H
