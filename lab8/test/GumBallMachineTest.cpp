#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/gumball_machine/CGumballMachine.h"

class MockState final : public IState
{
public:
	MOCK_METHOD(void, InsertQuarter, (), (override));
	MOCK_METHOD(void, EjectQuarter, (), (override));
	MOCK_METHOD(void, TurnCrank, (), (override));
	MOCK_METHOD(void, Dispense, (), (override));
	MOCK_METHOD(std::string, ToString, (), (const, override));
};

std::string GetExpectedMachineStringState(unsigned count, const std::string &stateString)
{
	return std::format(R"(
				Mighty Gumball, Inc.
				C++-enabled Standing Gumball Model #2016 (with state)
				Inventory: {} gumball{}
				Machine is {}
			)", count, count != 1 ? "s" : "", stateString);
}

TEST(CGumballMachineTest, InitializationWithPositiveCount)
{
	const CGumballMachine machine(5);

	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringState(5, "waiting for quarter"));
}

TEST(CGumballMachineTest, InitializationWithZero)
{
	const CGumballMachine machine(0);

	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringState(0, "sold out"));
}

TEST(CGumballMachineTest, EjectQuarter)
{
	const CGumballMachine machine(5);

	testing::internal::CaptureStdout();
	machine.EjectQuarter();
	const std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "You haven't inserted a quarter\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringState(5, "waiting for quarter"));
}

TEST(CGumballMachineTest, InsertQuarter)
{
	const CGumballMachine machine(5);

	testing::internal::CaptureStdout();
	machine.InsertQuarter();
	const std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "You inserted a quarter\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringState(5, "waiting for turn of crank"));
}

TEST(CGumballMachineTest, TurnCrank)
{
	const CGumballMachine machine(5);

	testing::internal::CaptureStdout();
	machine.TurnCrank();
	const std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "You turned but there's no quarter\nYou need to pay first\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringState(5, "waiting for quarter"));
}

TEST(CGumballMachineTest, ReleaseBall)
{
	const CGumballMachine machine(5);

	testing::internal::CaptureStdout();
	machine.InsertQuarter();
	machine.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringState(4, "waiting for quarter"));
}

TEST(CGumballMachineTest, ReleaseBallZeroBall)
{
	const CGumballMachine machine(0);

	testing::internal::CaptureStdout();
	machine.InsertQuarter();
	machine.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output,
	          "You can't insert a quarter, the machine is sold out\nYou turned but there's no gumballs\nNo gumball dispensed\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringState(0, "sold out"));
}

TEST(CGumballMachineTest, SetSoldOut)
{
	const CGumballMachine machine(1);

	testing::internal::CaptureStdout();
	machine.InsertQuarter();
	machine.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output,
	          "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringState(0, "sold out"));
}
