#include <iostream>
#include <gtest\gtest.h>
#include "T_Timer.h"
//#include "T_Timer.h"
#include "T_States.h"
#include "T_Math.h"
#include "T_Monster.h"

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);

	int success = RUN_ALL_TESTS();

	std::cin.get();

	return success;
}
