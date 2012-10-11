#include "State.h"

State::State(StateManager* p_parent)
{
	m_parent = p_parent;
}
State::~State()
{
}

void State::onEntry()
{
	// Base class should have this empty.
}