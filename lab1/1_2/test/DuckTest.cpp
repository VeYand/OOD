#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "../lib/Duck/Dance/IDanceBehavior.h"
#include "../lib/Duck/Duck.h"
#include "../lib/Duck/Fly/FlyWithWings.h"
#include "../lib/Duck/Quack/QuackBehavior.h"
#include "MockDanceBehavior.h"
#include "MockFlyBehavior.h"
#include "MockQuackBehavior.h"
#include "MockQuackPolicy.h"

class TestDuck final : public Duck
{
public:
	TestDuck(
		std::unique_ptr<IFlyBehavior>&& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quackBehavior,
		std::unique_ptr<IDanceBehavior>&& danceBehavior,
		std::unique_ptr<IQuackPolicy>&& quackPolicy)
		: Duck(std::move(flyBehavior), std::move(quackBehavior), std::move(danceBehavior), std::move(quackPolicy))
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

	TestDuck duck(
		std::make_unique<MockFlyBehavior>(),
		std::make_unique<MockQuackBehavior>(),
		std::move(mockDanceBehavior),
		std::make_unique<MockQuackPolicy>()
	);

	duck.Dance();
}

TEST(DuckTest, DuckQuacksBeforeAndAfterFlightBasedOnPolicy)
{
	auto mockFlyBehavior = std::make_unique<MockFlyBehavior>();
	auto mockQuackBehavior = std::make_unique<MockQuackBehavior>();
	auto mockQuackPolicy = std::make_unique<MockQuackPolicy>();

	EXPECT_CALL(*mockFlyBehavior, GetFlightCount()).WillOnce(testing::Return(1));
	EXPECT_CALL(*mockFlyBehavior, GetNextFlightCount()).WillOnce(testing::Return(2));
	EXPECT_CALL(*mockFlyBehavior, Fly()).Times(1);

	EXPECT_CALL(*mockQuackPolicy, ShouldQuack(2, false)).WillOnce(testing::Return(true));
	EXPECT_CALL(*mockQuackPolicy, ShouldQuack(2, true)).WillOnce(testing::Return(true));
	EXPECT_CALL(*mockQuackBehavior, Quack()).Times(2);

	TestDuck duck(
		std::move(mockFlyBehavior),
		std::move(mockQuackBehavior),
		std::make_unique<MockDanceBehavior>(),
		std::move(mockQuackPolicy)
	);

	duck.Fly();
}

TEST(DuckTest, DuckDoesNotQuackBeforeOrAfterFlightWhenPolicyDoesNotAllow)
{
	auto mockFlyBehavior = std::make_unique<MockFlyBehavior>();
	auto mockQuackBehavior = std::make_unique<MockQuackBehavior>();
	auto mockQuackPolicy = std::make_unique<MockQuackPolicy>();

	EXPECT_CALL(*mockFlyBehavior, GetFlightCount()).WillOnce(testing::Return(1));
	EXPECT_CALL(*mockFlyBehavior, GetNextFlightCount()).WillOnce(testing::Return(2));
	EXPECT_CALL(*mockFlyBehavior, Fly()).Times(1);

	EXPECT_CALL(*mockQuackPolicy, ShouldQuack(2, false)).WillOnce(testing::Return(false));
	EXPECT_CALL(*mockQuackPolicy, ShouldQuack(2, true)).WillOnce(testing::Return(false));
	EXPECT_CALL(*mockQuackBehavior, Quack()).Times(0);

	TestDuck duck(
		std::move(mockFlyBehavior),
		std::move(mockQuackBehavior),
		std::make_unique<MockDanceBehavior>(),
		std::move(mockQuackPolicy)
	);

	duck.Fly();
}