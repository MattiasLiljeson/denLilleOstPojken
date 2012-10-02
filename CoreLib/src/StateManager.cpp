#include "StateManager.h"

StateManager::StateManager(IODevice* p_io)
{
	m_io = p_io;
	m_inGameState = new InGameState(this, m_io);
	m_menuState = new MenuState(this, m_io);
	m_currentState = m_desiredState = m_menuState;
	m_terminated = false;
}
StateManager::~StateManager()
{
	delete m_inGameState;
	delete m_menuState;
}
void StateManager::requestStateChange(State* p_newState)
{
	if (p_newState == m_inGameState || p_newState == m_menuState)
	{
		m_desiredState = p_newState;
	}
}

void StateManager::update(float p_dt)
{
	if (m_desiredState != m_currentState)
	{
		switchState();
	}
	m_currentState->update(p_dt);
}
void StateManager::draw(float p_dt)
{
	m_currentState->draw(p_dt);
}

State* StateManager::getCurrentState()
{
	return m_currentState;
}
State* StateManager::getDesiredState()
{
	return m_desiredState;
}
State* StateManager::getMenuState()
{
	return m_menuState;
}
State* StateManager::getInGameState()
{
	return m_inGameState;
}

void StateManager::switchState()
{
	m_currentState = m_desiredState;
}
void StateManager::terminate()
{
	m_terminated = true;
}
bool StateManager::isTerminated()
{
	return m_terminated;
}