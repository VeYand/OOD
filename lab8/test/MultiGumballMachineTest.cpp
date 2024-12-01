#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/multi_gumball_machine/CMultiGumballMachine.h"
#include "../src/multi_gumball_machine/State/IState.h"

using namespace multi_gumball_machine;

class MockState final : public IState
{
public:
	MOCK_METHOD(void, InsertQuarter, (), (override));
	MOCK_METHOD(void, EjectQuarter, (), (override));
	MOCK_METHOD(void, TurnCrank, (), (override));
	MOCK_METHOD(void, Dispense, (), (override));
	MOCK_METHOD(void, Refill, (unsigned), (override));
	MOCK_METHOD(std::string, ToString, (), (const, override));
};

std::string GetExpectedMachineStringMultiState(unsigned count, const std::string &stateString)
{
	return std::format(R"(
				Mighty Gumball, Inc.
				C++-enabled Standing Gumball Model #2016 (with state)
				Inventory: {} gumball{}
				Machine is {}
			)", count, count != 1 ? "s" : "", stateString);
}

TEST(CMultiGumballMachineTest, InitializationWithPositiveCount)
{
	const CMultiGumballMachine machine(5);

	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringMultiState(5, "waiting for quarter"));
}

TEST(CMultiGumballMachineTest, InitializationWithZero)
{
	const CMultiGumballMachine machine(0);

	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringMultiState(0, "sold out"));
}

TEST(CMultiGumballMachineTest, EjectQuarter)
{
	const CMultiGumballMachine machine(5);

	testing::internal::CaptureStdout();
	machine.EjectQuarter();
	const std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "You haven't inserted a quarter\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringMultiState(5, "waiting for quarter"));
}

TEST(CMultiGumballMachineTest, InsertQuarter)
{
	const CMultiGumballMachine machine(5);

	testing::internal::CaptureStdout();
	machine.InsertQuarter();
	const std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "You inserted a quarter\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringMultiState(5, "waiting for turn of crank"));
}

TEST(CMultiGumballMachineTest, TurnCrank)
{
	const CMultiGumballMachine machine(5);

	testing::internal::CaptureStdout();
	machine.TurnCrank();
	const std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "You turned but there's no quarter\nYou need to pay first\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringMultiState(5, "waiting for quarter"));
}

TEST(CMultiGumballMachineTest, Refill)
{
	const CMultiGumballMachine machine(1);

	testing::internal::CaptureStdout();
	machine.Refill(5);
	const std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "Added gumball\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringMultiState(5, "waiting for quarter"));
}

TEST(CMultiGumballMachineTest, ReleaseBall)
{
	const CMultiGumballMachine machine(5);

	testing::internal::CaptureStdout();
	machine.InsertQuarter();
	machine.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringMultiState(4, "waiting for quarter"));
}

TEST(CMultiGumballMachineTest, ReleaseBallZeroBall)
{
	const CMultiGumballMachine machine(0);

	testing::internal::CaptureStdout();
	machine.InsertQuarter();
	machine.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output,
	          "You can't insert a quarter, the machine is sold out\nYou turned but there's no gumballs\nNo gumball dispensed\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringMultiState(0, "sold out"));
}

TEST(CMultiGumballMachineTest, SetSoldOut)
{
	const CMultiGumballMachine machine(1);

	testing::internal::CaptureStdout();
	machine.InsertQuarter();
	machine.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output,
	          "You inserted a quarter\nYou turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringMultiState(0, "sold out"));
}

TEST(CMultiGumballMachineTest, GetMaxQuarterCount)
{
	const CMultiGumballMachine machine(6);
	testing::internal::CaptureStdout();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You inserted a quarter\nYou inserted another quarter\nYou inserted another quarter\nYou inserted another quarter\nYou inserted another quarter\nYou can't insert another quarter\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringMultiState(6, "waiting for turn of crank"));
}

TEST(CMultiGumballMachineTest, ReturnAllQuarters)
{
	const CMultiGumballMachine machine(6);
	testing::internal::CaptureStdout();
	machine.InsertQuarter();
	machine.EjectQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You inserted a quarter\nQuarter returned\n");
	EXPECT_EQ(machine.ToString(), GetExpectedMachineStringMultiState(6, "waiting for quarter"));
}