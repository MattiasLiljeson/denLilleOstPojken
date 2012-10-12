#ifndef TESTTILE_H
#define TESTTILE_H

#include "Test.h"
#include <Tile.h>

class Test_Tile: public Test
{
private:
	void test1()
	{
	}
	void test2()
	{
	}
public:
	Test_Tile(): Test("TILE")
	{
	}
	void setup()
	{
		Tile* t = new Tile(true, TilePosition(4, 5), 10, 15, NULL);

		float w = t->getWidth();
		float h = t->getHeight();

		TilePosition posT = t->getTilePosition();

		fVector2 pos = t->getPosition();

		newEntry(TestData("Width", w == 10));
		newEntry(TestData("Height", h == 15));
		newEntry(TestData("Tile Position", posT == TilePosition(4, 5)));
		newEntry(TestData("Position", pos == fVector2(45, 82.5f)));
		newEntry(TestData("State", t->isFree()));
	}	
};	

#endif