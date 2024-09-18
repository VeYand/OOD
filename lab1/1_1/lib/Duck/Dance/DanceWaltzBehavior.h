#ifndef DANCEWALTZ_H
#define DANCEWALTZ_H

#include "IDanceBehavior.h"
#include <iostream>

class DanceWaltzBehavior final : public IDanceBehavior
{
public:
	void Dance() const override
	{
		std::cout << "I'm dancing a waltz!!" << std::endl;
	}
};

#endif // DANCEWALTZ_H
