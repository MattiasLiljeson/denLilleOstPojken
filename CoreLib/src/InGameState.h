#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "State.h"

class InGameState: public State
{
private:
public:
	InGameState(StateManager* p_parent);
	void update(float p_dt);
	void draw(float p_dt);
};

#endif
