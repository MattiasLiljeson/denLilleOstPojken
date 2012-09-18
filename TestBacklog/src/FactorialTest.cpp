#include <gtest\gtest.h>
#include "Factorial.h"

TEST(FactorialTest_PositiveValues, FactorialTest)
{
	EXPECT_EQ(6, Factorial(3));
	EXPECT_EQ(24, Factorial(4));
}

TEST(FactorialTest_NegativeValues, FactorialTest)
{
	EXPECT_EQ(-1, Factorial(-100));
}