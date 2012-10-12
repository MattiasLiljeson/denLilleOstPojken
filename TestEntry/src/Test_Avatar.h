#ifndef TESTAVATAR_H
#define TESTAVATAR_H

#include "Test.h"
#include <Avatar.h>
#include <Tilemap.h>

class Test_Avatar: public Test
{
private:
	void test1()
	{
		//Testing a null based avatar
		Avatar avatar(NULL, NULL, NULL, NULL);
		newEntry(TestData("Null Tile", avatar.getCurrentTile() == NULL));
		newEntry(TestData("Not Moving", avatar.getDirection() == Direction::NONE));
		newEntry(TestData("Interpolation", avatar.getTileInterpolationFactor() == 0));

		InputInfo inf;
		avatar.update(0.5f, inf);

		float dt = avatar.getTileInterpolationFactor();
		newEntry(TestData("Time Interval", dt <= 1 && dt >= 0));
	}
	void test2()
	{
		//Testing a typical avatar
		Tile** tiles = new Tile*[2];
		tiles[0] = new Tile(true, TilePosition(0, 0), 10, 10, NULL);
		tiles[1] = new Tile(true, TilePosition(1, 0), 10, 10, NULL);

		Tilemap tmap(2, 1, tiles);

		Avatar avatar(NULL, &tmap, tiles[0], NULL);

		newEntry(TestData("Correct Tile", avatar.getCurrentTile() == tiles[0]));
		newEntry(TestData("Correct Position", avatar.getCurrentTile()->getTilePosition() == TilePosition(0, 0)));

		InputInfo inf;
		inf.keys[InputInfo::RIGHT] = InputInfo::KEYPRESSED;
		avatar.update(0.5f, inf);

		newEntry(TestData("Correct Direction", avatar.getDirection() == Direction::RIGHT));
	}
public:
	Test_Avatar(): Test("AVATAR")
	{
	}
	void setup()
	{
		newSection("Null Avatar");
		test1();
		newSection("Normal Avatar");
		test2();
	}	
};	

#endif