#ifndef T_AVATAR_H
#define T_AVATAR_H

#include "gtest/gtest.h"
#include <Avatar.h>
#include <Tilemap.h>
#include <Tile.h>
#include <MapLoader.h>
#include <GameStats.h>

class T_Avatar : public ::testing::Test
{
protected:
	T_Avatar(){
	}
	virtual ~T_Avatar(){
	}
	virtual void SetUp()
	{
		MapLoader mapParser;
		mapParser.parseMap("..\\Maps\\test_map.txt");
		vector<int> data = mapParser.getMap();

		bool* types = new bool[100];
		for (int i = 0; i < 100; i++)
		{
			if (data[i] == WALL_CENTER)
				types[i] = false;
			else
				types[i] = true;
		}

		tm = new Tilemap(10, 10, types, NULL);
		stats = new GameStats(NULL);
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (data[i*10+j] == AVATAR_SPAWN)
				{
					av = new Avatar(NULL, tm, tm->getTile(TilePosition(j, i)), stats);
				}
			}
		}
	}
	virtual void TearDown()
	{
		delete tm;
		delete av;
	}

	Tilemap* tm;
	Avatar* av;
	GameStats* stats;
};

TEST_F(T_Avatar, Namn)
{
	ASSERT_TRUE(av->getCurrentTile() != NULL);
	ASSERT_TRUE(av->getDirection() == Direction::NONE);

	InputInfo inputInfo;
	inputInfo.keys[InputInfo::LEFT] = InputInfo::KEYPRESSED;
	inputInfo.keys[InputInfo::RIGHT] = InputInfo::KEYUP;
	inputInfo.keys[InputInfo::UP] = InputInfo::KEYUP;
	inputInfo.keys[InputInfo::DOWN] = InputInfo::KEYUP;
	av->update(0.1f, inputInfo);

	float inter = av->getTileInterpolationFactor();
	ASSERT_TRUE(av->getDirection() == Direction::LEFT);
	ASSERT_TRUE(inter > 0);
	stats->setSpeeded();
	av->update(0.1f, inputInfo);
	ASSERT_TRUE(inter * 2 < av->getTileInterpolationFactor());
}

#endif