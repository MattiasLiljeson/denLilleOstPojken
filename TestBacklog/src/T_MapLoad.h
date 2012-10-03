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
		delete stats;
	}
	MapLoader* mapLoader;
	GameStats* stats;
};

TEST_F(T_MapLoader,parseFromFile)
{
	ASSERT_EQ(mapLoader->parseMap("../Maps/test_map.txt", NULL, stats), GAME_OK);
}

TEST_F(T_MapLoader,parseMissingFile)
{
	ASSERT_EQ(mapLoader->parseMap("../Maps2/test_map.txt", NULL, stats), GAME_FAIL);
}

TEST_F(T_MapLoader,parseInvalidFile)
{
	ASSERT_EQ(mapLoader->parseMap("../Maps/invalid.txt", NULL, stats), GAME_FAIL);
}

#endif