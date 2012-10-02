#ifndef T_MAPLOADER_H
#define T_MAPLOADER_H

#include <MapLoader.h>
#include <vector>
#include "gtest/gtest.h"

class T_MapLoader : public ::testing::Test
{
protected:
	T_MapLoader(){
	}
	virtual ~T_MapLoader(){
	}
	virtual void SetUp(){
		mapLoader = new MapLoader();
	}
	virtual void TearDown(){
		delete mapLoader;
	}
	MapLoader* mapLoader;
};

TEST_F(T_MapLoader,parseFromFile)
{
	std::vector<int> data = mapLoader->parseMap("..\\Maps\\test_map.txt");
	ASSERT_TRUE(data.at(0)==EMPTY);
	ASSERT_TRUE(data.at(1)==WALL_CENTER);
	ASSERT_TRUE(data.at(9)==PILL);
	ASSERT_TRUE(data.at(19)==AVATAR_SPAWN);
	ASSERT_TRUE(data.at(29)==MONSTER_SPAWN);
	ASSERT_TRUE(data.at(39)==SPEEDPILL);
}

#endif