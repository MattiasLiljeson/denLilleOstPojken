#ifndef STATE_H
#define STATE_H

class StateManager;

class State
{
protected:
	StateManager* m_parent;
public:
	State(StateManager* p_parent);
	virtual void update(float p_dt) = 0;
	virtual void draw(float p_dt) = 0;
};

#endif