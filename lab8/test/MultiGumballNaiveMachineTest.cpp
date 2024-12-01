#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/multi_gumball_machine/naive/CMultiGumballNaiveMachine.h"

using namespace multi_gumball_naive_machine;

TEST (MultiGumballNaiveMachineTest, InitializationWithZero)
{
}

TEST (MultiGumballNaiveMachineTest, InitializationPositive)
{
}

TEST (MultiGumballNaiveMachineTest, InsertQuarterCantInsertAnother)
{
}

TEST (MultiGumballNaiveMachineTest, InsertQuarterCantInsertOnSoldOut)
{
}

TEST (MultiGumballNaiveMachineTest, InsertQuarterCantInsertOnNoQuarter)
{
}

TEST (MultiGumballNaiveMachineTest, InsertQuarterCantInsertOnHasQuarter)
{
}

TEST (MultiGumballNaiveMachineTest, InsertQuarterCantInsertOnSold)
{
}

TEST (MultiGumballNaiveMachineTest, EjectQuarterOnSoldOutPosotiveQuarterCount)
{
}

TEST (MultiGumballNaiveMachineTest, EjectQuarterOnSoldOutZeroQuarterCount)
{
}

TEST (MultiGumballNaiveMachineTest, EjectQuarterOnNoQuarter)
{
}

TEST (MultiGumballNaiveMachineTest, EjectQuarterOnHasQuarter)
{
}

TEST (MultiGumballNaiveMachineTest, EjectQuarterOnSold)
{
}

TEST (MultiGumballNaiveMachineTest, TurnCrankOnSoldOut)
{
}

TEST (MultiGumballNaiveMachineTest, TurnCrankOnNoQuarter)
{
}

TEST (MultiGumballNaiveMachineTest, TurnCrankOnHasQuarter)
{
}

TEST (MultiGumballNaiveMachineTest, TurnCrankOnSold)
{
}

TEST (MultiGumballNaiveMachineTest, RefillOnSoldOutZeroBallCount)
{
}

TEST (MultiGumballNaiveMachineTest, RefillOnSoldOutNonZeroBallCountZeroQuarterCount)
{
}

TEST (MultiGumballNaiveMachineTest, RefillOnSoldOutNonZeroBallCountNonZeroQuarterCount)
{
}

TEST (MultiGumballNaiveMachineTest, RefillOnNoQuarter)
{
}

TEST (MultiGumballNaiveMachineTest, RefillOnHasQuarter)
{
}

TEST (MultiGumballNaiveMachineTest, RefillOnSold)
{
}

TEST (MultiGumballNaiveMachineTest, ToStringOnSoldOut)
{
}

TEST (MultiGumballNaiveMachineTest, ToStringOnNoQuarter)
{
}

TEST (MultiGumballNaiveMachineTest, ToStringOnHasQuarter)
{
}

TEST (MultiGumballNaiveMachineTest, ToStringOnSold)
{
}