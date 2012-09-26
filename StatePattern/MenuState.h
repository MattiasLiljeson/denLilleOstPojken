#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"

class MenuState: public State
{
private:
public:
	MenuState(StateManager* p_parent);
	void update(float p_dt);
	void draw(float p_dt);
};

#endif