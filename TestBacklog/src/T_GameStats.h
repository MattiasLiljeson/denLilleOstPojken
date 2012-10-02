#ifndef T_GAMESTATS_H
#define T_GAMESTATS_H

#include "gtest/gtest.h"
#include <GameStats.h>

class T_GameStats : public ::testing::Test
{
protected:
	T_GameStats(){
	}
	virtual ~T_GameStats(){
	}
	virtual void SetUp()
	{
	}
	virtual void TearDown()
	{
	}
};

TEST_F(T_GameStats, Namn)
{
	GameStats stats;
	stats.addPill();
	stats.addPill();
	ASSERT_TRUE(stats.getNumPills() == 2);
	stats.pillEaten();
	ASSERT_TRUE(stats.getNumPills() == 1);
}

#endif