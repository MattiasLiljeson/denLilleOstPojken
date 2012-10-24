#ifndef TESTTILEMAP_H
#define TESTTILEMAP_H

#include "Test.h"
#include <Tilemap.h>

class Test_Tilemap: public Test
{
private:
	void test1()
	{
	}
	void test2()
	{
	}
public:
	Test_Tilemap(): Test("TILEMAP")
	{
	}
	void setup()
	{
		Tile** tiles = new Tile*[6];
		tiles[0] = new Tile(true, TilePosition(0, 0), 10, 10, NULL);
		tiles[1] = new Tile(true, TilePosition(1, 0), 10, 10, NULL);
		tiles[2] = new Tile(true, TilePosition(0, 1), 10, 10, NULL);
		tiles[3] = new Tile(true, TilePosition(1, 1), 10, 10, NULL);
		tiles[4] = new Tile(false, TilePosition(0, 2), 10, 10, NULL);
		tiles[5] = new Tile(false, TilePosition(1, 2), 10, 10, NULL);
		Tilemap map(2, 3, tiles);

		newSection("General");
		newEntry(TestData("Width", map.getWidth() == 2));
		newEntry(TestData("Height", map.getHeight() == 3));
		newEntry(TestData("Get Tile", map.getTile(TilePosition(0,2)) == tiles[4]));
		newEntry(TestData("Get Invalid Tile", !map.getTile(TilePosition(0,3))));

		newSection("Position Queries");
		newEntry(TestData("Valid Position", map.isValidPosition(tiles[0]->getTilePosition())));
		newEntry(TestData("Invalid Position +X", !map.isValidPosition(TilePosition(2, 1))));
		newEntry(TestData("Invalid Position -X", !map.isValidPosition(TilePosition(-1, 1))));
		newEntry(TestData("Invalid Position +Y", !map.isValidPosition(TilePosition(0, 3))));
		newEntry(TestData("Invalid Position -Y", !map.isValidPosition(TilePosition(0, -1))));
	}	
};	

#endif