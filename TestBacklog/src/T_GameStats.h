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
		gameStats = new GameStats(NULL);
	}
	virtual void TearDown()
	{
		delete gameStats;
	}
	GameStats* gameStats;
};

TEST_F(T_GameStats, addRemovePill)
{
	GameStats stats(NULL);
	stats.addPill();
	stats.addPill();
	ASSERT_TRUE(stats.getNumPills() == 2);
	stats.pillEaten();
	ASSERT_TRUE(stats.getNumPills() == 1);
}

TEST_F(T_GameStats, checkPointSystem)
{
	gameStats->addScore(MONSTER_KILLED);
	gameStats->addScore(PILL_EATEN);

	ASSERT_EQ(gameStats->getScore(),MONSTER_KILLED+PILL_EATEN);
}

#endif