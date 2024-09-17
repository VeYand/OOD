#ifndef MOCKQUACKPOLICY_H
#define MOCKQUACKPOLICY_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../lib/Duck/QuackPolicy/IQuackPolicy.h"

class MockQuackPolicy final : public IQuackPolicy
{
public:
	MOCK_METHOD(bool, ShouldQuack, (int flightCount, bool isAfterFlight), (const, override));
};

#endif // MOCKQUACKPOLICY_H
