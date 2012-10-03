#ifndef T_MAPLOADER_H
#define T_MAPLOADER_H

#include <MapLoader.h>
#include <vector>
#include "gtest/gtest.h"
#include <GameStats.h>

class T_MapLoader : public ::testing::Test
{
protected:
	T_MapLoader(){
	}
	virtual ~T_MapLoader(){
	}
	virtual void SetUp(){
		mapLoader = new MapLoader();
		stats = new GameStats(NULL);
	}
	virtual void TearDown(){
		delete mapLoader;
	}
	MapLoader* mapLoader;
	GameStats* stats;
};

TEST_F(T_MapLoader,parseFromFile)
{
	//mapLoader->parseMap("..\\Maps\\test_map.txt", NULL, NULL);
	/*std::vector<int> data = mapLoader->getMap();
	ASSERT_TRUE(data.at(0)==EMPTY);
	ASSERT_TRUE(data.at(1)==WALL_CENTER);
	ASSERT_TRUE(data.at(9)==PILL);
	ASSERT_TRUE(data.at(19)==AVATAR_SPAWN);
	ASSERT_TRUE(data.at(29)==MONSTER_SPAWN);
	ASSERT_TRUE(data.at(39)==SPEEDPILL);*/
}

#endif