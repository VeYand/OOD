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

class TestDuck final : public Duck
{
public:
	explicit TestDuck(
		std::unique_ptr<IFlyBehavior>&& flyBehavior,
		std::unique_ptr<IQuackBehavior>&& quackBehavior,
		std::unique_ptr<IDanceBehavior>&& danceBehavior
		)
		: Duck(
			std::move(flyBehavior),
			std::move(quackBehavior),
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

	EXPECT_CALL(*mockDanceBehavior, Dance()).Times(1);

	const TestDuck duck(
		std::make_unique<MockFlyBehavior>(),
		std::make_unique<MockQuackBehavior>(),
		std::move(mockDanceBehavior)
		);
	duck.Dance();
}

TEST(DuckTest, FlyableDuckQuacksAfterEvenFlightTest)
{
	auto mockFlyBehavior = std::make_unique<MockFlyBehavior>();
	auto mockQuackBehavior = std::make_unique<MockQuackBehavior>();

	EXPECT_CALL(*mockFlyBehavior, GetFlightCount())
		.WillOnce(::testing::Return(1));
	EXPECT_CALL(*mockFlyBehavior, CanFly())
		.WillRepeatedly(testing::Return(true));
	EXPECT_CALL(*mockFlyBehavior, Fly()).Times(1);
	EXPECT_CALL(*mockQuackBehavior, Quack()).Times(0);

	TestDuck duck(
		std::move(mockFlyBehavior),
		std::move(mockQuackBehavior),
		std::make_unique<MockDanceBehavior>()
		);

	duck.Fly();

	auto mockFlyBehavior2 = std::make_unique<MockFlyBehavior>();
	auto mockQuackBehavior2 = std::make_unique<MockQuackBehavior>();

	EXPECT_CALL(*mockFlyBehavior2, GetFlightCount())
		.WillOnce(::testing::Return(2));
	EXPECT_CALL(*mockFlyBehavior2, CanFly())
		.WillRepeatedly(testing::Return(true));
	EXPECT_CALL(*mockFlyBehavior2, Fly()).Times(1);
	EXPECT_CALL(*mockQuackBehavior2, Quack()).Times(1);

	TestDuck duck2(
		std::move(mockFlyBehavior2),
		std::move(mockQuackBehavior2),
		std::make_unique<MockDanceBehavior>()
		);

	duck2.Fly();
}

TEST(DuckTest, NotFlyableDuckNotQuacksAfterEvenFlight)
{
	auto mockFlyBehavior = std::make_unique<MockFlyBehavior>();
	auto mockQuackBehavior = std::make_unique<MockQuackBehavior>();

	EXPECT_CALL(*mockFlyBehavior, GetFlightCount())
		.WillRepeatedly(::testing::Return(0));
	EXPECT_CALL(*mockFlyBehavior, CanFly())
		.WillRepeatedly(testing::Return(false));
	EXPECT_CALL(*mockFlyBehavior, Fly()).Times(2);
	EXPECT_CALL(*mockQuackBehavior, Quack()).Times(0);

	TestDuck duck(
		std::move(mockFlyBehavior),
		std::move(mockQuackBehavior),
		std::make_unique<MockDanceBehavior>()
		);

	duck.Fly();
	duck.Fly();
}