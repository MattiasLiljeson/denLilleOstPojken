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
		GameStats stats(NULL);
		m_entries.push_back(TestData("Initial Pill Count", stats.getNumPills() == 0));
		m_entries.push_back(TestData("Null Timer", stats.getGameTimer() == 0));
		m_entries.push_back(TestData("Initial Score", stats.getScore() == 0));
		m_entries.push_back(TestData("Not Speeded", !stats.isSpeeded()));
		m_entries.push_back(TestData("Not Super", !stats.isSuperMode()));
		stats.addScore(100);
		stats.addPill();
		stats.addPill();
		m_entries.push_back(TestData("Pill Count", stats.getNumPills() == 2));
		m_entries.push_back(TestData("Score", stats.getScore() == 100));
	}	
};

#endif