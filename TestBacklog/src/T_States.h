#ifndef T_STATES_H
#define T_STATES_H

#include "gtest/gtest.h"
#include <StateManager.h>

class T_States : public ::testing::Test
{
protected:
	T_States(){
	}
	virtual ~T_States(){
	}
	virtual void SetUp(){
		mgr = new StateManager();
	}
	virtual void TearDown(){
		delete mgr;
	}
	StateManager* mgr;

};

TEST_F(T_States, Namn)
{
	ASSERT_TRUE(mgr->getCurrentState());

}
#endif