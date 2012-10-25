#ifndef TESTBOMB_H
#define TESTBOMB_H

#include "Test.h"
#include <Bomb.h>
#include <Tilemap.h>

class Test_Bomb: public Test
{
private:
public:
	Test_Bomb(): Test("BOMB")
	{
	}
	void setup()
	{
		vector<pair<Tile*, SpriteInfo*>> data;
		Bomb b(NULL, data, NULL, NULL, NULL, NULL);
		newEntry(TestData("Construction", true));
		b.update(0.5f, InputInfo());
		newEntry(TestData("Update", true));
	}	
};	

#endif