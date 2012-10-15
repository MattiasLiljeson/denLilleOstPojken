#include "State.h"

State::State(StateManager* p_parent)
{
	m_parent = p_parent;
	m_resourcesAllocated=false;
}
State::~State()
{
}

bool State::onEntry()
{
	// Base class should have no implementation.
	return false;
}

bool State::onExit()
{
	// Base class should have no implementation.
	return false;
}