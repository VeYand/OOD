#ifndef MUTEQUAKBEHAVIOR_H
#define MUTEQUAKBEHAVIOR_H

#include "IQuackBehavior.h"

class MuteQuackBehavior final : public IQuackBehavior
{
public:
	void Quack() override {}
};

#endif // MUTEQUAKBEHAVIOR_H
