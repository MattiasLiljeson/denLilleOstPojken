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
	}	
};

#endif