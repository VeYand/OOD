#ifndef DANCEBEHAVIOR_H
#define DANCEBEHAVIOR_H

#include <functional>
#include <iostream>

using DanceBehavior = std::function<void()>;

inline DanceBehavior CreateDanceWaltzBehavior()
{
	return []() {
		std::cout << "I'm dancing a waltz!!" << std::endl;
	};
}

inline DanceBehavior CreateDanceMinuetBehavior()
{
	return []() {
		std::cout << "I'm dancing a minuet!!" << std::endl;
	};
}

inline DanceBehavior CreateNoDanceBehavior()
{
	return []() {
	};
}

#endif // DANCEBEHAVIOR_H