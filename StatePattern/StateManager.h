#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "InGameState.h"
#include "MenuState.h"

class StateManager
{
private:
	State* m_inGameState;
	State* m_menuState;
	State* m_currentState;
	State* m_desiredState;
public:
	StateManager();

	void requestStateChange(State* p_newState);
	void update(float p_dt);
	void draw(float p_dt);

	State* getCurrentState();
	State* getMenuState();
	State* getInGameState();

private:
	void switchState();
};

#endif