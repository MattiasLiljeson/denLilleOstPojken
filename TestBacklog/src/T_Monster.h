#ifndef T_MONSTER_H
#define T_MONSTER_H

#include "gtest/gtest.h"
#include <Monster.h>

class T_Monster : public ::testing::Test
{
protected:
	T_Monster(){
	}
	virtual ~T_Monster(){
	}
	virtual void SetUp(){
	}
	virtual void TearDown(){
	}
};

TEST_F(T_Monster, Namn)
{
	Tile* t = NULL;
	Monster m(t, NULL, NULL);
	ASSERT_TRUE(t == m.getCurrentTile());
}

#endif