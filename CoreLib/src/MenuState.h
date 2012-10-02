#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"

class MenuState: public State
{
private:
	IODevice* m_io;
public:
	MenuState(StateManager* p_parent, IODevice* p_io);
	void update(float p_dt);
	void draw(float p_dt);
};

#endif