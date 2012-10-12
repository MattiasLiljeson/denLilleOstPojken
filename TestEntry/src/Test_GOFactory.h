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
		m_entries.push_back(TestData("Create Avatar", av != NULL));
		
		Monster* mon = factory.CreateMonster(NULL, NULL);
		m_entries.push_back(TestData("Create Monster", mon != NULL));
		
		Pill* pill = factory.CreatePill(NULL, NULL);
		m_entries.push_back(TestData("Create Pill", pill != NULL));

		SuperPill* super = factory.CreateSuperPill(NULL, NULL);
		m_entries.push_back(TestData("Create Super Pill", super != NULL));

		SpeedPill* speed = factory.CreateSpeedPill(NULL, NULL);
		m_entries.push_back(TestData("Create Speed Pill", speed != NULL));

		MenuItem* menuItem = factory.createMenuItem();
		m_entries.push_back(TestData("Create Menu Item", menuItem != NULL));

		Switch* goSwitch = factory.CreateSwitch(NULL, NULL, NULL, vector<TilePosition>());
		m_entries.push_back(TestData("Create Switch", goSwitch != NULL));

		Tile* tile = factory.CreateTile(true, TilePosition(0, 0), 10, 10);
		m_entries.push_back(TestData("Create Tile", tile != NULL));

		Glyph* glyph = factory.CreateGlyph("../Textures/testglyph.png",0.0f,0.0f,fVector2(8.0f,8.0f));
		m_entries.push_back(TestData("Create Glyph", glyph != NULL));

		bool init[] = {true};
		Tilemap* map = factory.CreateTileMap(1, 1, init);
		m_entries.push_back(TestData("Create Tilemap", map != NULL));

		delete av;
		delete mon;
		delete pill;
		delete super;
		delete speed;
		delete menuItem;
		delete tile;
		delete goSwitch;
		delete map;
	}	
};

#endif