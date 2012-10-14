#ifndef TESTMONSTER_H
#define TESTMONSTER_H

#include "Test.h"
#include <Monster.h>
#include <Tilemap.h>

class Test_Monster: public Test
{
private:
	void nullMonster()
	{
		newSection("Null Monster");
		Monster monster(NULL, NULL, NULL);
		newEntry(TestData("Null Tile", !monster.getCurrentTile()));
		newEntry(TestData("Null Position", monster.getPostion() == fVector2(0, 0)));
		newEntry(TestData("Null Radius", monster.getRadius() == 0));
		newEntry(TestData("Not Dead", !monster.isDead()));

		InputInfo inf;
		monster.update(0.5f, inf); 

		monster.kill();
		newEntry(TestData("Dead", monster.isDead()));
	}
	void actualMonster()
	{
		Tile** tiles = new Tile*[4];
		tiles[0] = new Tile(true, TilePosition(0, 0), 10, 15, NULL);
		tiles[1] = new Tile(true, TilePosition(1, 0), 10, 15, NULL);
		tiles[2] = new Tile(true, TilePosition(0, 1), 10, 15, NULL);
		tiles[3] = new Tile(true, TilePosition(1, 1), 10, 15, NULL);

		Tilemap map(2, 2, tiles);
		newSection("Actual Monster");
		Monster monster(NULL, tiles[2], &map);

		newEntry(TestData("Correct Tile", monster.getCurrentTile() == tiles[2]));
		newEntry(TestData("Correct Position", monster.getPostion() == fVector2(0, 0)));

		Avatar avatar(NULL, &map, tiles[0], NULL);
		monster.addMonsterAI(&avatar, NULL, &map);

		InputInfo inf;

		int loopindex = 0;
		while (monster.getCurrentTile() != avatar.getCurrentTile() && loopindex < 100)
			monster.update(0.5f, inf);

		newEntry(TestData("Finds Target", loopindex < 100));
		newEntry(TestData("Is Alive", !monster.isDead()));
		monster.kill();
		newEntry(TestData("Is Dead", monster.isDead()));
	}
public:
	Test_Monster(): Test("MONSTER")
	{
	}
	void setup()
	{
		nullMonster();
		actualMonster();
	}	
};	

#endif