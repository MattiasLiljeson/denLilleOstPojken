#include "State.h"

State::State(StateManager* p_parent)
{
	m_parent = p_parent;
}
State::~State()
{
}

bool State::onEntry()
{
	// Base class should have no implementation.
	return false;
}