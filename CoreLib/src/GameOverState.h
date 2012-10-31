#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "State.h"
#include "GOFactory.h"
#include "MenuItem.h"

class StateManager;
class GameOverState : public State
{
public:
	GameOverState(StateManager* p_parent, IODevice* p_io);
	virtual ~GameOverState();

	bool onEntry();
	bool onExit();

	virtual void update(float p_dt);
	virtual void draw(float p_dt);
private:
	void initGameOverItems();
private:
	IODevice*	m_io;
	GOFactory*	m_factory;
	MenuItem*	m_gameOverText;
	MenuItem*	m_scoreText;
	MenuItem*	m_continueText;

};

#endif