#ifndef T_STATES_H
#define T_STATES_H

#include "gtest/gtest.h"
#include <StateManager.h>

/*class T_States : public ::testing::Test
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

};*/

TEST(T_States, Namn)
{
	StateManager* mgr = new StateManager();
	State* curr = mgr->getCurrentState();
	State* inGame = mgr->getInGameState();
	State* menu = mgr->getMenuState();
	State* outerState = new InGameState(mgr);
	ASSERT_TRUE(curr);
	ASSERT_TRUE(inGame);
	ASSERT_TRUE(menu);
	ASSERT_TRUE(menu == curr || inGame == curr);

	mgr->requestStateChange(menu);
	mgr->update(0);
	
	ASSERT_TRUE(menu == mgr->getCurrentState());
	ASSERT_TRUE(menu == mgr->getDesiredState());

	mgr->requestStateChange(inGame);

	ASSERT_FALSE(inGame == mgr->getCurrentState());
	ASSERT_TRUE(inGame == mgr->getDesiredState());

	mgr->update(0);

	ASSERT_TRUE(inGame == mgr->getCurrentState());
	ASSERT_TRUE(inGame == mgr->getDesiredState());

	mgr->requestStateChange(outerState);
	mgr->update(0);
	
	ASSERT_FALSE(outerState == mgr->getCurrentState());



	delete outerState;

}
#endif