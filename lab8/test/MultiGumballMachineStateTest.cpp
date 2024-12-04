#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/multi_gumball_machine/CMultiGumballMachine.h"

using namespace multi_gumball_machine;

class MockMultiGumballMachine final : public IMultiGumballMachine
{
public:
	MOCK_METHOD(void, ReleaseBall, (), (override));
	MOCK_METHOD(unsigned, GetBallCount, (), (const, override));
	MOCK_METHOD(unsigned, GetQuarterCount, (), (const, override));
	MOCK_METHOD(unsigned, GetMaxQuarterCount, (), (const, override));
	MOCK_METHOD(void, AddQuarter, (), (override));
	MOCK_METHOD(void, RefillBall, (unsigned), (override));
	MOCK_METHOD(void, ReturnAllQuarters, (), (override));
	MOCK_METHOD(void, SetSoldOutState, (), (override));
	MOCK_METHOD(void, SetNoQuarterState, (), (override));
	MOCK_METHOD(void, SetSoldState, (), (override));
	MOCK_METHOD(void, SetHasQuarterState, (), (override));
};

TEST(CHasQuarterMultiStateTest, InsertQuarter)
{
	MockMultiGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, GetMaxQuarterCount()).WillOnce(testing::Return(5));
	EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockMachine, AddQuarter()).Times(1);

	hasQuarterState.InsertQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You inserted another quarter\n");
}

TEST(CHasQuarterMultiStateTest, InsertQuarterOverflow)
{
	MockMultiGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, GetMaxQuarterCount()).WillOnce(testing::Return(5));
	EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(5));

	hasQuarterState.InsertQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You can't insert another quarter\n");
}

TEST(CHasQuarterMultiStateTest, EjectQuarter)
{
	MockMultiGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	EXPECT_CALL(mockMachine, ReturnAllQuarters()).Times(1);
	EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

	hasQuarterState.EjectQuarter();
}

TEST(CHasQuarterMultiStateTest, TurnCrankSold)
{
	MockMultiGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(5));
	EXPECT_CALL(mockMachine, SetSoldState()).Times(1);

	hasQuarterState.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You turned...\n");
}

TEST(CHasQuarterMultiStateTest, TurnCrankNoQuarters)
{
	MockMultiGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

	hasQuarterState.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "No quarters left.\n");
}

TEST(CHasQuarterMultiStateTest, Dispense)
{
	MockMultiGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	testing::internal::CaptureStdout();

	hasQuarterState.Dispense();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "No gumball dispensed\n");
}

TEST(CHasQuarterMultiStateTest, Refill)
{
	MockMultiGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(5));
	EXPECT_CALL(mockMachine, RefillBall(5)).Times(1);

	hasQuarterState.Refill(5);

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Gumball machine is refilled\n");
}

TEST(CHasQuarterMultiStateTest, RefillZero)
{
	MockMultiGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockMachine, RefillBall(0)).Times(1);
	EXPECT_CALL(mockMachine, SetSoldOutState).Times(1);

	hasQuarterState.Refill(0);

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Gumball machine is refilled\n");
}

TEST(CHasQuarterMultiStateTest, ToString)
{
	MockMultiGumballMachine mockMachine;
	CHasQuarterState hasQuarterState(mockMachine);

	const auto str = hasQuarterState.ToString();

	EXPECT_EQ(str, "waiting for turn of crank");
}

TEST(CNoQuarterMultiStateTest, InsertQuarter)
{
	MockMultiGumballMachine mockMachine;
	CNoQuarterState noQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, AddQuarter()).Times(1);
	EXPECT_CALL(mockMachine, SetHasQuarterState()).Times(1);

	noQuarterState.InsertQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You inserted a quarter\n");
}

TEST(CNoQuarterMultiStateTest, EjectQuarter)
{
	MockMultiGumballMachine mockMachine;
	CNoQuarterState noQuarterState(mockMachine);
	testing::internal::CaptureStdout();

	noQuarterState.EjectQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You haven't inserted a quarter\n");
}

TEST(CNoQuarterMultiStateTest, TurnCrank)
{
	MockMultiGumballMachine mockMachine;
	CNoQuarterState noQuarterState(mockMachine);
	testing::internal::CaptureStdout();

	noQuarterState.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You turned but there's no quarter\n");
}

TEST(CNoQuarterMultiStateTest, Dispense)
{
	MockMultiGumballMachine mockMachine;
	CNoQuarterState noQuarterState(mockMachine);
	testing::internal::CaptureStdout();

	noQuarterState.Dispense();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You need to pay first\n");
}

TEST(CNoQuarterMultiStateTest, Refill)
{
	MockMultiGumballMachine mockMachine;
	CNoQuarterState noQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(5));
	EXPECT_CALL(mockMachine, RefillBall(5)).Times(1);

	noQuarterState.Refill(5);

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Gumball machine is refilled\n");
}

TEST(CNoQuarterMultiStateTest, RefillZero)
{
	MockMultiGumballMachine mockMachine;
	CNoQuarterState noQuarterState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockMachine, RefillBall(0)).Times(1);
	EXPECT_CALL(mockMachine, SetSoldOutState).Times(1);

	noQuarterState.Refill(0);

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Gumball machine is refilled\n");
}

TEST(CNoQuarterMultiStateTest, ToString)
{
	MockMultiGumballMachine mockMachine;
	const CNoQuarterState noQuarterState(mockMachine);

	const auto str = noQuarterState.ToString();

	EXPECT_EQ(str, "waiting for quarter");
}

TEST(CSoldOutMultiStateTest, InsertQuarter)
{
	MockMultiGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	testing::internal::CaptureStdout();

	soldOutState.InsertQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You can't insert a quarter, the machine is sold out\n");
}

TEST(CSoldOutMultiStateTest, EjectQuarterReturnAll)
{
	MockMultiGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(2));
	EXPECT_CALL(mockMachine, ReturnAllQuarters()).Times(1);

	soldOutState.EjectQuarter();
}

TEST(CSoldOutMultiStateTest, EjectQuarterEmpty)
{
	MockMultiGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	testing::internal::CaptureStdout();
	EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(0));

	soldOutState.EjectQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You can't eject, you haven't inserted a quarter yet\n");
}

TEST(CSoldOutMultiStateTest, TurnCrank)
{
	MockMultiGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	testing::internal::CaptureStdout();

	soldOutState.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "You turned but there's no gumballs\n");
}

TEST(CSoldOutMultiStateTest, Dispense)
{
	MockMultiGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	testing::internal::CaptureStdout();

	soldOutState.Dispense();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "No gumball dispensed\n");
}

TEST(CSoldOutMultiStateTest, RefillSoldOut)
{
	MockMultiGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	testing::internal::CaptureStdout();
	constexpr auto ballsCount = 0;
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(ballsCount));
	EXPECT_CALL(mockMachine, RefillBall(ballsCount)).Times(1);

	soldOutState.Refill(ballsCount);

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Gumball machine is refilled\n");
}

TEST(CSoldOutMultiStateTest, RefillHasQuarter)
{
	MockMultiGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	testing::internal::CaptureStdout();
	constexpr auto ballsCount = 3;
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(ballsCount));
	EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockMachine, RefillBall(ballsCount)).Times(1);
	EXPECT_CALL(mockMachine, SetHasQuarterState()).Times(1);

	soldOutState.Refill(ballsCount);

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Gumball machine is refilled\n");
}

TEST(CSoldOutMultiStateTest, RefillNoQuarter)
{
	MockMultiGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);
	testing::internal::CaptureStdout();
	constexpr auto ballsCount = 3;
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(ballsCount));
	EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockMachine, RefillBall(ballsCount)).Times(1);
	EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

	soldOutState.Refill(ballsCount);

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Gumball machine is refilled\n");
}

TEST(CSoldOutMultiStateTest, ToString)
{
	MockMultiGumballMachine mockMachine;
	CSoldOutState soldOutState(mockMachine);

	const auto str = soldOutState.ToString();

	EXPECT_EQ(str, "sold out");
}

TEST(CSoldMultiStateTest, InsertQuarter)
{
	MockMultiGumballMachine mockMachine;
	CSoldState soldState(mockMachine);
	testing::internal::CaptureStdout();

	soldState.InsertQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Please wait, we're already giving you a gumball\n");
}

TEST(CSoldMultiStateTest, EjectQuarter)
{
	MockMultiGumballMachine mockMachine;
	CSoldState soldState(mockMachine);
	testing::internal::CaptureStdout();

	soldState.EjectQuarter();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Sorry you already turned the crank\n");
}

TEST(CSoldMultiStateTest, TurnCrank)
{
	MockMultiGumballMachine mockMachine;
	CSoldState soldState(mockMachine);
	testing::internal::CaptureStdout();

	soldState.TurnCrank();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Turning twice doesn't get you another gumball\n");
}

TEST(CSoldMultiStateTest, DispenseWhenGumballsRemain)
{
	MockMultiGumballMachine mockMachine;
	CSoldState soldState(mockMachine);

	EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockMachine, SetNoQuarterState()).Times(1);

	soldState.Dispense();
}

TEST(CSoldMultiStateTest, DispenseWhenGumballsRemainAndQuarters)
{
	MockMultiGumballMachine mockMachine;
	CSoldState soldState(mockMachine);

	EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockMachine, GetQuarterCount()).WillOnce(testing::Return(1));
	EXPECT_CALL(mockMachine, SetHasQuarterState()).Times(1);

	soldState.Dispense();
}

TEST(CSoldMultiStateTest, DispenseWhenOutOfGumballs)
{
	MockMultiGumballMachine mockMachine;
	CSoldState soldState(mockMachine);
	testing::internal::CaptureStdout();

	EXPECT_CALL(mockMachine, ReleaseBall()).Times(1);
	EXPECT_CALL(mockMachine, GetBallCount()).WillOnce(testing::Return(0));
	EXPECT_CALL(mockMachine, SetSoldOutState()).Times(1);

	soldState.Dispense();

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Oops, out of gumballs\n");
}

TEST(CSoldMultiStateTest, Refill)
{
	MockMultiGumballMachine mockMachine;
	CSoldState soldState(mockMachine);
	testing::internal::CaptureStdout();

	soldState.Refill(5);

	const std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "Cannot refill machine when giving you a gumball\n");
}

TEST(CSoldMultiStateTest, ToString)
{
	MockMultiGumballMachine mockMachine;
	const CSoldState soldState(mockMachine);

	const auto str = soldState.ToString();

	EXPECT_EQ(str, "delivering a gumball");
}
