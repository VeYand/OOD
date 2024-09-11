#include <gtest/gtest.h>
#include "../lib/Duck/Duck.h"
#include "../lib/Duck/DecoyDuck.h"
#include "../lib/Duck/MallardDuck.h"
#include "../lib/Duck/ModelDuck.h"
#include "../lib/Duck/RedheadDuck.h"
#include "../lib/Duck/RubberDuck.h"
#include <sstream>

const std::string noDanceOutput;
const std::string minuetDanceOutput = "I'm dancing a minuet!!\n";
const std::string waltzDanceOutput = "I'm dancing a waltz!!\n";

void assertDance(const Duck &duck, const std::string& danceOutput)
{
	const std::stringstream buffer;
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
	duck.Dance();
	std::cout.rdbuf(oldCoutBuffer);

	ASSERT_EQ(buffer.str(), danceOutput);
}

TEST (DuckTest, MallardDuckDance)
{
	const MallardDuck duck;
	assertDance(duck, waltzDanceOutput);
}

TEST (DuckTest, RedheadDuckDance)
{
	const RedheadDuck duck;
	assertDance(duck, minuetDanceOutput);
}

TEST (DuckTest, ModelDuckDance)
{
	const ModelDuck duck;
	assertDance(duck, noDanceOutput);
}

TEST (DuckTest, RubberDuckDance)
{
	const RubberDuck duck;
	assertDance(duck, noDanceOutput);
}


TEST (DuckTest, DecoyDuckDance)
{
	const DecoyDuck duck;
	assertDance(duck, noDanceOutput);
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}