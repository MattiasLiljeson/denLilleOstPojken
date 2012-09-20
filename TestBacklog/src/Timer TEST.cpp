#include "Timer.h"
#include <gtest\gtest.h>

TEST(Timer_getDeltaTime, plainTest)
{
	Timer timer;

	EXPECT_EQ(0, timer.getDeltaTime());
}