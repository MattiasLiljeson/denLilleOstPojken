#ifndef T_MONSTER_H
#define T_MONSTER_H

#include "gtest/gtest.h"
#include <Monster.h>
#include <Tilemap.h>
#include <Tile.h>
#include <MapLoader.h>

class T_Monster : public ::testing::Test
{
protected:
	T_Monster(){
	}
	virtual ~T_Monster(){
	}
	virtual void SetUp()
	{
		MapLoader mapParser;
		vector<int> data = mapParser.parseMap("..\\Maps\\test_map.txt");

		bool* types = new bool[100];
		for (int i = 0; i < 100; i++)
		{
			if (data[i] == WALL_CENTER)
				types[i] = false;
			else
				types[i] = true;
		}

		tm = new Tilemap(10, 10, types, NULL);

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (data[i*10+j] == MONSTER_SPAWN)
				{
					m.push_back(new Monster(tm->getTile(TilePosition(j, i)), tm, NULL));
				}
			}
		}
	}
	virtual void TearDown()
	{
		delete tm;
		for (int i = 0; i < m.size(); i++)
			delete m[i];
	}

	Tilemap* tm;
	vector<Monster*> m;
};

TEST_F(T_Monster, Namn)
{
	ASSERT_TRUE(tm->getTile(TilePosition(0, 0))->isFree());
	ASSERT_FALSE(tm->getTile(TilePosition(1, 0))->isFree());
	ASSERT_FALSE(tm->isValidPosition(TilePosition(-1, -1)));
	ASSERT_TRUE(tm->isValidPosition(TilePosition(9, 9)));
	ASSERT_TRUE(tm->getWidth() == 10);
	ASSERT_TRUE(tm->getHeight() == 10);

	Tile* t = tm->getTile(TilePosition(6, 9));
	Tile* t2 = tm->getTile(TilePosition(6, 7));
	ASSERT_TRUE(tm->closestFreeTile(t) == t2);
	ASSERT_FALSE(tm->closestFreeTile(t2) == t);

	ASSERT_TRUE(m[0]->getCurrentTile() != NULL);
}

#endif