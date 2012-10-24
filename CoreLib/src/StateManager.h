#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "InGameState.h"
#include "MenuState.h"
#include "GameOverState.h"
#include "VictoryState.h"
#include <Timer.h>
#include "MapHeader.h"

enum
{
	STATE_CHANGE_FAIL = 2
};

struct CommonResources
{
	int totalScore;
};

class StateManager
{
private:
	State* m_inGameState;
	State* m_menuState;
	State* m_gameOverState;
	State* m_victoryState;
	State* m_currentState;
	State* m_desiredState;

	IODevice* m_io;
	bool m_terminated;
	Timer* m_timer;

	CommonResources m_commonResources;

public:
	StateManager(IODevice* p_io, Timer* p_timer);
	virtual ~StateManager();

	int requestStateChange(State* p_newState);
	void update(float p_dt);
	void draw(float p_dt);

	State* getCurrentState();
	State* getDesiredState();
	State* getMenuState();
	State* getInGameState();
	State* getGameOverState();
	State* getVictoryState();

	void terminate();
	bool isTerminated();

	Timer* getNewTimerInstance();

	CommonResources* getCommonResources();

private:
	void switchState();
};

#endif