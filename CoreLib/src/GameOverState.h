#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "State.h"

class StateManager;
class GameOverState : public State
{
public:
	GameOverState(StateManager* p_parent);
	virtual ~GameOverState();

	virtual void update(float p_dt);
	virtual void draw(float p_dt);
private:

};

#endif