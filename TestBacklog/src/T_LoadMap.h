#ifndef T_LOADMAP_H
#define T_LOADMAP_H

#include "gtest/gtest.h"
#include <LoadMap.h>

class T_LoadMap : public ::testing::Test
{
protected:
	T_LoadMap(){
	}
	virtual ~T_LoadMap(){
	}
	virtual void SetUp(){
		mapParser = new LoadMap();
	}
	virtual void TearDown(){
		delete mapParser;
	}
	LoadMap* mapParser;
};

TEST_F(T_LoadMap, CheckIfParsingIsWorking){
	vector<int> map;
	map = mapParser->parseMap("C:\Den-lila-ostpojken\WinEntry\Map\test_map.txt");

	ASSERT_EQ(map.at(0),1);
}
#endif