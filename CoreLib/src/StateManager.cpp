#include "StateManager.h"

StateManager::StateManager(IODevice* p_io, Timer* p_timer)
{
	m_io = p_io;
	m_timer = p_timer;
	m_inGameState = new InGameState(this, m_io);
	m_menuState = new MenuState(this, m_io);
	m_currentState = m_desiredState = m_menuState;
	// Call the curren state's entry function.
	m_currentState->onEntry();
	m_terminated = false;
}
StateManager::~StateManager()
{
	delete m_inGameState;
	delete m_menuState;
}
int StateManager::requestStateChange(State* p_newState)
{
	if(p_newState != m_desiredState)
	{
		if (p_newState == m_inGameState || p_newState == m_menuState)
		{
			m_desiredState = p_newState;
			return GAME_OK;
		}
	}

	return STATE_CHANGE_FAIL;
}

void StateManager::update(float p_dt)
{
	if (m_desiredState != m_currentState)
	{
		switchState();
		// Call the curren state's entry function.
		m_currentState->onEntry();
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
Timer* StateManager::getNewTimerInstance()
{
	return m_timer->newInstance();
}