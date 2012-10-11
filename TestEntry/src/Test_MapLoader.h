#ifndef TESTMAPLOADER_H
#define TESTMAPLOADER_H

#include "Test.h"
#include <MapLoader.h>

class Test_MapLoader: public Test
{
private:
public:
	Test_MapLoader(): Test("MAPLOADER")
	{
	}
	void setup()
	{
		MapLoader loader;
		m_entries.push_back(TestData("Missing File", loader.parseMap("../Maps/invalid.txt", NULL, NULL, NULL) == GAME_FAIL));	
		m_entries.push_back(TestData("Missing Factory", loader.parseMap("../Maps/1.txt", NULL, NULL, NULL) == GAME_FAIL));

		//GOFactory* factory = new GOFactory(NULL);
		//m_entries.push_back(TestData("Missing Factory", loader.parseMap("../Maps/1.txt", NULL, NULL, factory) == GAME_FAIL));
		//delete factory;
		
		//loader.parseMap("../Maps/1.txt", NULL, NULL, NULL);
		/*GameStats stats(NULL);
		m_entries.push_back(TestData("Initial Pill Count", stats.getNumPills() == 0));
		m_entries.push_back(TestData("Null Timer", stats.getGameTimer() == 0));
		m_entries.push_back(TestData("Initial Score", stats.getScore() == 0));
		m_entries.push_back(TestData("Not Speeded", !stats.isSpeeded()));
		m_entries.push_back(TestData("Not Super", !stats.isSuperMode()));
		stats.addScore(100);
		stats.addPill();
		stats.addPill();
		m_entries.push_back(TestData("Pill Count", stats.getNumPills() == 2));
		m_entries.push_back(TestData("Score", stats.getScore() == 100));*/
	}	
};

#endif