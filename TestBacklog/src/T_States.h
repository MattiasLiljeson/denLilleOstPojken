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
		m_manager = new StateManager(NULL, NULL);
		m_current = m_manager->getCurrentState();
		m_inGame = m_manager->getInGameState();
		m_menu = m_manager->getMenuState();
		m_outerState = new InGameState(m_manager, NULL);
	}
	virtual void TearDown(){
		delete m_manager;
		delete m_outerState;
	}
	StateManager* m_manager;
	State* m_current;
	State* m_inGame;
	State* m_menu;
	State* m_outerState;

};
/*
TEST_F(T_States, Namn)
{
	
	ASSERT_TRUE(m_current);
	ASSERT_TRUE(m_inGame);
	ASSERT_TRUE(m_menu);
	ASSERT_TRUE(m_menu == m_current || m_inGame == m_current);

	m_manager->requestStateChange(m_menu);
	m_manager->update(0);
	
	ASSERT_TRUE(m_menu == m_manager->getCurrentState());

	m_manager->requestStateChange(m_inGame);

	ASSERT_FALSE(m_inGame == m_manager->getCurrentState());
	ASSERT_TRUE(m_inGame == m_manager->getDesiredState());

	m_manager->update(0);
	m_manager->update(0);
	ASSERT_TRUE(m_inGame == m_manager->getCurrentState());
	m_manager->update(0);
	ASSERT_TRUE(m_inGame == m_manager->getCurrentState());
	ASSERT_TRUE(m_inGame == m_manager->getDesiredState());

	m_manager->requestStateChange(m_outerState);
	m_manager->update(0);
	
	ASSERT_FALSE(m_outerState == m_manager->getCurrentState());
	delete m_outerState;

}
*/
TEST_F(T_States, switchStateOk)
{
	ASSERT_EQ(m_manager->requestStateChange(m_menu), GAME_OK);
}

TEST_F(T_States, switchStateNotValid)
{
	ASSERT_EQ(m_manager->requestStateChange(m_outerState), STATE_CHANGE_FAIL);
}

TEST_F(T_States, switchStateToCurrentState)
{
	ASSERT_EQ(m_manager->requestStateChange(m_inGame), STATE_CHANGE_FAIL);
}
#endif