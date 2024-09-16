#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "../lib/Duck/Dance/IDanceBehavior.h"
#include "../lib/Duck/Duck.h"
#include "../lib/Duck/Fly/FlyWithWings.h"
#include "../lib/Duck/Quack/QuackBehavior.h"
#include "MockDanceBehavior.h"

class TestDuck final : public Duck
{
public:
	explicit TestDuck(std::unique_ptr<IDanceBehavior>&& danceBehavior)
		: Duck(
			std::make_unique<FlyWithWings>(),
			std::make_unique<QuackBehavior>(),
			std::move(danceBehavior)
			)
	{
	}

	void Display() const override
	{
		std::cout << "I'm test duck" << std::endl;
	}
};

TEST(DuckTest, DuckCanDance)
{
	auto mockDanceBehavior = std::make_unique<MockDanceBehavior>();

	EXPECT_CALL(*mockDanceBehavior, Dance()).Times(testing::AtLeast(1));

	const TestDuck duck(std::move(mockDanceBehavior));
	duck.Dance();
}

