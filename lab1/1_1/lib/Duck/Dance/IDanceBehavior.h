#ifndef LAB01_SIMUDUCK_IDANCEBEHAVIOR_H
#define LAB01_SIMUDUCK_IDANCEBEHAVIOR_H

struct IDanceBehavior
{
	virtual ~IDanceBehavior() = default;

	virtual void Dance() = 0; // убарть константность
};

#endif // LAB01_SIMUDUCK_IDANCEBEHAVIOR_H
