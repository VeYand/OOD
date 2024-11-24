#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/gumball_machine/CGumballMachine.h"

using namespace gumball_machine;

class MockGumballMachine final : public IGumballMachine
{
public:
	MOCK_METHOD(void, ReleaseBall, (), (override));
	MOCK_METHOD(unsigned, GetBallCount, (), (const, override));
	MOCK_METHOD(void, SetSoldOutState, (), (override));
	MOCK_METHOD(void, SetNoQuarterState, (), (override));
	MOCK_METHOD(void, SetSoldState, (), (override));
	MOCK_METHOD(void, SetHasQuarterState, (), (override));
};

TEST(CHasQuarterStateTest, InsertQuarter)
{
	MockGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	testing::internal::CaptureStdout();

	hasQuarterState.InsertQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You can't insert another quarter\n");
}

TEST(CHasQuarterStateTest, EjectQuarter)
{
	MockGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

	hasQuarterState.EjectQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Quarter returned\n");
}

TEST(CHasQuarterStateTest, TurnCrank)
{
	MockGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, SetSoldState()).Times(1);

	hasQuarterState.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You turned...\n");
}

TEST(CHasQuarterStateTest, Dispense)
{
	MockGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	testing::internal::CaptureStdout();

	hasQuarterState.Dispense();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "No gumball dispensed\n");
}

TEST(CHasQuarterStateTest, ToString)
{
	MockGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);

	const auto str = hasQuarterState.ToString();

	EXPECT_EQ(str, "waiting for turn of crank");
}

TEST(CNoQuarterStateTest, InsertQuarter)
{
	MockGumballMachine mockMachine;
	CNoQuarterState noQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, SetHasQuarterState()).Times(1);

	noQuarterState.InsertQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You inserted a quarter\n");
}

TEST(CNoQuarterStateTest, EjectQuarter)
{
	MockGumballMachine mockMachine;
	CNoQuarterState noQuarterState(mockMachine);
	testing::internal::CaptureStdout();

	noQuarterState.EjectQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You haven't inserted a quarter\n");
}

TEST(CNoQuarterStateTest, TurnCrank)
{
	MockGumballMachine mockMachine;
	CNoQuarterState noQuarterState(mockMachine);
	testing::internal::CaptureStdout();

	noQuarterState.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You turned but there's no quarter\n");
}

TEST(CNoQuarterStateTest, Dispense)
{
	MockGumballMachine mockMachine;
	CNoQuarterState noQuarterState(mockMachine);
	testing::internal::CaptureStdout();

	noQuarterState.Dispense();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You need to pay first\n");
}

TEST(CNoQuarterStateTest, ToString)
{
	MockGumballMachine mockMachine;
	const CNoQuarterState noQuarterState(mockMachine);

	const auto str = noQuarterState.ToString();

	EXPECT_EQ(str, "waiting for quarter");
}

TEST(CSoldOutStateTest, InsertQuarter)
{
	MockGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	testing::internal::CaptureStdout();

	soldOutState.InsertQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You can't insert a quarter, the machine is sold out\n");
}

TEST(CSoldOutStateTest, EjectQuarter)
{
	MockGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	testing::internal::CaptureStdout();

	soldOutState.EjectQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You can't eject, you haven't inserted a quarter yet\n");
}

TEST(CSoldOutStateTest, TurnCrank)
{
	MockGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	testing::internal::CaptureStdout();

	soldOutState.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You turned but there's no gumballs\n");
}

TEST(CSoldOutStateTest, Dispense)
{
	MockGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	testing::internal::CaptureStdout();

	soldOutState.Dispense();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "No gumball dispensed\n");
}

TEST(CSoldOutStateTest, ToString)
{
	MockGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);

	const auto str = soldOutState.ToString();

	EXPECT_EQ(str, "sold out");
}


TEST(CSoldStateTest, InsertQuarter)
{
	MockGumballMachine mockMachine;
	CSoldState soldState(mockMachine);
	testing::internal::CaptureStdout();

	soldState.InsertQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Please wait, we're already giving you a gumball\n");
}

TEST(CSoldStateTest, EjectQuarter)
{
	MockGumballMachine mockMachine;
	CSoldState soldState(mockMachine);
	testing::internal::CaptureStdout();

	soldState.EjectQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Sorry you already turned the crank\n");
}

TEST(CSoldStateTest, TurnCrank)
{
	MockGumballMachine mockMachine;
	CSoldState soldState(mockMachine);
	testing::internal::CaptureStdout();

	soldState.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Turning twice doesn't get you another gumball\n");
}

TEST(CSoldStateTest, DispenseWhenGumballsRemain)
{
	MockGumballMachine mockMachine;
	CSoldState soldState(mockMachine);
	testing::internal::CaptureStdout();

	EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

	soldState.Dispense();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "");
}

TEST(CSoldStateTest, DispenseWhenOutOfGumballs)
{
	MockGumballMachine mockMachine;
	CSoldState soldState(mockMachine);
	testing::internal::CaptureStdout();

	EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockMachine, SetSoldOutState()).Times(1);

	soldState.Dispense();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Oops, out of gumballs\n");
}

TEST(CSoldStateTest, ToString)
{
	MockGumballMachine mockMachine;
	const CSoldState soldState(mockMachine);

	const auto str = soldState.ToString();

	EXPECT_EQ(str, "delivering a gumball");
}
