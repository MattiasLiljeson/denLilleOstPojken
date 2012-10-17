#ifndef TESTGOFACTORY_H
#define TESTGOFACTORY_H

#include "Test.h"
#include <GOFactory.h>

class Test_GOFactory: public Test
{
private:
public:
	Test_GOFactory(): Test("GOFACTORY")
	{
	}
	void setup()
	{
		GOFactory factory(NULL);
		
		Avatar* av = factory.CreateAvatar(NULL, NULL, NULL);
		newEntry(TestData("Create Avatar", av != NULL));
		
		Monster* mon = factory.CreateMonster(NULL, NULL);
		newEntry(TestData("Create Monster", mon != NULL));
		
		Pill* pill = factory.CreatePill(NULL, NULL);
		newEntry(TestData("Create Pill", pill != NULL));

		SuperPill* super = factory.CreateSuperPill(NULL, NULL);
		newEntry(TestData("Create Super Pill", super != NULL));

		SpeedPill* speed = factory.CreateSpeedPill(NULL, NULL);
		newEntry(TestData("Create Speed Pill", speed != NULL));

		//MenuItem* menuItem = factory.createMenuItem();
		newEntry(TestData("Create Menu Item", false));

		Switch* goSwitch = factory.CreateSwitch(NULL, NULL, NULL, vector<TilePosition>());
		newEntry(TestData("Create Switch", goSwitch != NULL));

		Tile* tile = factory.CreateTile(true, TilePosition(0, 0), 10, 10);
		newEntry(TestData("Create Tile", tile != NULL));

		Glyph* glyph = factory.CreateGlyph("../Textures/testglyph.png",0.0f,0.0f,fVector2(8.0f,8.0f));
		newEntry(TestData("Create Glyph", glyph != NULL));

		bool init[] = {true};
		Tilemap* map = factory.CreateTileMap(1, 1, init);
		newEntry(TestData("Create Tilemap", map != NULL));

		delete av;
		delete mon;
		delete pill;
		delete super;
		delete speed;
		//delete menuItem;
		delete tile;
		delete goSwitch;
		delete map;
		delete glyph;
	}	
};

#endif