#ifndef NODANCEBEHAIVOR_H
#define NODANCEBEHAIVOR_H

#include "IDanceBehavior.h"

class NoDanceBehavior final : public IDanceBehavior
{
public:
	void Dance() const override
	{
	}
};

#endif // NODANCEBEHAIVOR_H
