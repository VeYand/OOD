#ifndef MOCKFLYBEHAVIOR_H
#define MOCKFLYBEHAVIOR_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../lib/Duck/Fly/IFlyBehavior.h"

class MockFlyBehavior final : public IFlyBehavior
{
public:
	MOCK_METHOD(void, Fly, (), (override));
	MOCK_METHOD(int, GetFlightCount, (), (const, override));
	MOCK_METHOD(bool, CanFly, (), (const, override));
};

#endif // MOCKFLYBEHAVIOR_H
