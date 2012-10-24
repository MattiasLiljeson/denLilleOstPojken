#ifndef TESTGAMESTATS_H
#define TESTGAMESTATS_H

#include "Test.h"
#include <GameStats.h>

class Test_GameStats: public Test
{
private:
public:
	Test_GameStats(): Test("GAMESTATS")
	{
	}
	void setup()
	{
		GameStats stats(NULL, 20);
		newEntry(TestData("Initial Pill Count", stats.getNumPills() == 0));
		newEntry(TestData("Null Timer", stats.getGameTimer() == 0));
		newEntry(TestData("Initial Score", stats.getScore() == 0));
		newEntry(TestData("Not Speeded", !stats.isSpeeded()));
		newEntry(TestData("Not Super", !stats.isSuperMode()));
		stats.addScore(100);
		stats.addPill();
		stats.addPill();
		newEntry(TestData("Pill Count", stats.getNumPills() == 2));
		newEntry(TestData("Score", stats.getScore() == 100));
	}	
};

#endif