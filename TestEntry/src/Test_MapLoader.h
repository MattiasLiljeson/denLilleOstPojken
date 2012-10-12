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
		newEntry(TestData("Missing File", loader.parseMap("../Maps/invalid.txt", NULL, NULL, NULL) == GAME_FAIL));	
		newEntry(TestData("Missing Factory", loader.parseMap("../Maps/1.txt", NULL, NULL, NULL) == GAME_FAIL));

		//GOFactory* factory = new GOFactory(NULL);
		//newEntry(TestData("Missing Factory", loader.parseMap("../Maps/1.txt", NULL, NULL, factory) == GAME_FAIL));
		//delete factory;
		
		//loader.parseMap("../Maps/1.txt", NULL, NULL, NULL);
		/*GameStats stats(NULL);
		newEntry(TestData("Initial Pill Count", stats.getNumPills() == 0));
		newEntry(TestData("Null Timer", stats.getGameTimer() == 0));
		newEntry(TestData("Initial Score", stats.getScore() == 0));
		newEntry(TestData("Not Speeded", !stats.isSpeeded()));
		newEntry(TestData("Not Super", !stats.isSuperMode()));
		stats.addScore(100);
		stats.addPill();
		stats.addPill();
		newEntry(TestData("Pill Count", stats.getNumPills() == 2));
		newEntry(TestData("Score", stats.getScore() == 100));*/
	}	
};

#endif