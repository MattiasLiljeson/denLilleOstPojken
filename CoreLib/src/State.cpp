#include "State.h"

State::State(StateManager* p_parent)
{
	m_parent = p_parent;
	m_stateJustActivated = false;
}
State::~State()
{
}

void State::activateState()
{
	m_stateJustActivated = true;
}