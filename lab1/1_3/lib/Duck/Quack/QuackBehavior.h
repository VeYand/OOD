#ifndef QUACKBEHAVIOR_H
#define QUACKBEHAVIOR_H

#include <functional>
#include <iostream>

using QuackBehavior = std::function<void()>;

inline QuackBehavior CreateQuackBehavior()
{
	return []() {
		std::cout << "Quack Quack!!!" << std::endl;
	};
}

inline QuackBehavior CreateSqueakBehavior()
{
	return []() {
		std::cout << "Squeak!!!" << std::endl;
	};
}

inline QuackBehavior CreateMuteQuackBehavior()
{
	return []() {
	};
}

#endif // QUACKBEHAVIOR_H