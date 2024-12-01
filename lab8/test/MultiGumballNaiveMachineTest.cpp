#include <gtest/gtest.h>
#include "../src/multi_gumball_machine/naive/CMultiGumballNaiveMachine.h"

using namespace multi_gumball_naive_machine;

std::string GetExpectedNaiveMachineStringState(unsigned count, const std::string &stateString)
{
	return std::format(R"(
				Mighty Gumball, Inc.
				C++-enabled Standing Gumball Model #2016
				Inventory: {} gumball{}
				Machine is {}
			)", count, count != 1 ? "s" : "", stateString);
}

TEST(MultiGumballNaiveMachineTest, InitializationWithZero)
{
	CMultiGumballMachine machine(0);
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(0, "sold out"));
}

TEST(MultiGumballNaiveMachineTest, InitializationPositive)
{
	CMultiGumballMachine machine(3);
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(3, "waiting for quarter"));
}

TEST(MultiGumballNaiveMachineTest, InsertQuarterCantInsertAnother)
{
	CMultiGumballMachine machine(5);
	for (int i = 0; i < 5; ++i)
	{
		machine.InsertQuarter();
	}
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(5, "waiting for turn of crank"));
	machine.InsertQuarter();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(5, "waiting for turn of crank"));
}

TEST(MultiGumballNaiveMachineTest, InsertQuarterCantInsertOnSoldOut)
{
	CMultiGumballMachine machine(0);
	machine.InsertQuarter();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(0, "sold out"));
}

TEST(MultiGumballNaiveMachineTest, InsertQuarterCantInsertOnNoQuarter)
{
	CMultiGumballMachine machine(5);
	machine.InsertQuarter();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(5, "waiting for turn of crank"));
}

TEST(MultiGumballNaiveMachineTest, InsertQuarterCantInsertOnHasQuarter)
{
	CMultiGumballMachine machine(5);
	machine.InsertQuarter();
	machine.InsertQuarter();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(5, "waiting for turn of crank"));
}

TEST(MultiGumballNaiveMachineTest, InsertQuarterCantInsertOnSold)
{
	CMultiGumballMachine machine(1);
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.InsertQuarter();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(0, "sold out"));
}

TEST(MultiGumballNaiveMachineTest, EjectQuarterOnSoldOutPosotiveQuarterCount)
{
	CMultiGumballMachine machine(0);
	machine.InsertQuarter();
	machine.EjectQuarter();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(0, "sold out"));
}

TEST(MultiGumballNaiveMachineTest, EjectQuarterOnSoldOutZeroQuarterCount)
{
	CMultiGumballMachine machine(0);
	machine.EjectQuarter();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(0, "sold out"));
}

TEST(MultiGumballNaiveMachineTest, EjectQuarterOnNoQuarter)
{
	CMultiGumballMachine machine(5);
	machine.EjectQuarter();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(5, "waiting for quarter"));
}

TEST(MultiGumballNaiveMachineTest, EjectQuarterOnHasQuarter)
{
	CMultiGumballMachine machine(5);
	machine.InsertQuarter();
	machine.EjectQuarter();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(5, "waiting for quarter"));
}

TEST(MultiGumballNaiveMachineTest, EjectQuarterOnSold)
{
	CMultiGumballMachine machine(1);
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.EjectQuarter();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(0, "sold out"));
}

TEST(MultiGumballNaiveMachineTest, TurnCrankOnSoldOut)
{
	CMultiGumballMachine machine(0);
	machine.TurnCrank();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(0, "sold out"));
}

TEST(MultiGumballNaiveMachineTest, TurnCrankOnNoQuarter)
{
	CMultiGumballMachine machine(5);
	machine.TurnCrank();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(5, "waiting for quarter"));
}

TEST(MultiGumballNaiveMachineTest, TurnCrankOnHasQuarter)
{
	CMultiGumballMachine machine(5);
	machine.InsertQuarter();
	machine.TurnCrank();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(4, "waiting for quarter"));
}

TEST(MultiGumballNaiveMachineTest, TurnCrankOnSold)
{
	CMultiGumballMachine machine(1);
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.TurnCrank();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(0, "sold out"));
}

TEST(MultiGumballNaiveMachineTest, RefillOnSoldOutZeroBallCount)
{
	CMultiGumballMachine machine(0);
	machine.Refill(0);
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(0, "sold out"));
}

TEST(MultiGumballNaiveMachineTest, RefillOnSoldOutNonZeroBallCountZeroQuarterCount)
{
	CMultiGumballMachine machine(0);
	machine.Refill(3);
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(3, "waiting for quarter"));
}

TEST(MultiGumballNaiveMachineTest, RefillOnSoldOutNonZeroBallCountNonZeroQuarterCount)
{
	CMultiGumballMachine machine(0);
	testing::internal::CaptureStdout();
	machine.InsertQuarter();
	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You can't insert a quarter, the machine is sold out\n");
	machine.Refill(3);
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(3, "waiting for quarter"));
}

TEST(MultiGumballNaiveMachineTest, RefillOnNoQuarter)
{
	CMultiGumballMachine machine(5);
	machine.Refill(10);
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(10, "waiting for quarter"));
}

TEST(MultiGumballNaiveMachineTest, RefillOnHasQuarter)
{
	CMultiGumballMachine machine(5);
	machine.InsertQuarter();
	machine.Refill(10);
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(10, "waiting for turn of crank"));
}

TEST(MultiGumballNaiveMachineTest, RefillOnSold)
{
	CMultiGumballMachine machine(1);
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.Refill(10);
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(10, "waiting for quarter"));
}

TEST(MultiGumballNaiveMachineTest, ToStringOnSoldOut)
{
	CMultiGumballMachine machine(0);
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(0, "sold out"));
}

TEST(MultiGumballNaiveMachineTest, ToStringOnNoQuarter)
{
	CMultiGumballMachine machine(5);
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(5, "waiting for quarter"));
}

TEST(MultiGumballNaiveMachineTest, ToStringOnHasQuarter)
{
	CMultiGumballMachine machine(5);
	machine.InsertQuarter();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(5, "waiting for turn of crank"));
}

TEST(MultiGumballNaiveMachineTest, ToStringOnSold)
{
	CMultiGumballMachine machine(1);
	machine.InsertQuarter();
	machine.TurnCrank();
	EXPECT_EQ(machine.ToString(), GetExpectedNaiveMachineStringState(0, "sold out"));
}
