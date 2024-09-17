#ifndef MOCKDANCEBEHAVIOR_H
#define MOCKDANCEBEHAVIOR_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../lib/Duck/Dance/IDanceBehavior.h"

class MockDanceBehavior final : public IDanceBehavior
{
public:
	MOCK_METHOD(void, Dance, (), (override));
};

#endif // MOCKDANCEBEHAVIOR_H