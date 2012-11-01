#ifndef VICTORYSTATE_H
#define VICTORYSTATE_H

#include "State.h"
#include "GOFactory.h"
#include "MenuItem.h"

class StateManager;
class VictoryState : public State
{
public:
	VictoryState(StateManager* p_parent, IODevice* p_io);
	virtual ~VictoryState();

	bool onEntry();
	bool onExit();

	virtual void update(float p_dt);
	virtual void draw(float p_dt);
private:
	void initGameOverItems();
private:
	IODevice*	m_io;
	GOFactory*	m_factory;
	MenuItem*	m_victoryText;
	MenuItem*	m_scoreText;
	MenuItem*	m_continueText;

};

#endif