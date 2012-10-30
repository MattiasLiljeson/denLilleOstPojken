#include "StateManager.h"

StateManager::StateManager(IODevice* p_io, Timer* p_timer)
{
	m_io = p_io;
	m_timer = p_timer;

	m_commonResources.totalScore = 0;
	m_commonResources.unlockedLevels = readUnlockedMaps();
	MapHeader mh("../Maps/maps.txt");
	m_inGameState = new InGameState(this, m_io, mh.getMaps());
	m_menuState = new MenuState(this, m_io, mh.getMaps());
	m_gameOverState = new GameOverState(this, m_io);
	m_victoryState = new VictoryState(this, m_io);
	m_currentState = m_desiredState = m_menuState;
	// Call the curren state's entry function.
	m_currentState->onEntry();
	m_terminated = false;
}
StateManager::~StateManager()
{
	writeUnlockedMaps(m_commonResources.unlockedLevels);
	delete m_inGameState;
	delete m_menuState;
	delete m_gameOverState;
	delete m_victoryState;
}
int StateManager::requestStateChange(State* p_newState)
{
	if(p_newState != m_desiredState)
	{
		if (p_newState == m_inGameState || p_newState == m_menuState || p_newState == m_gameOverState || p_newState == m_victoryState)
		{
			m_desiredState = p_newState;
			return GAME_OK;
		}
	}

	return STATE_CHANGE_FAIL;
}

void StateManager::update(float p_dt)
{
	if (m_io && !m_io->isRunning())
	{
		m_terminated = true;
		return; // FFS!!!!
	}

	if (m_desiredState != m_currentState)
	{
		m_currentState->onExit(); // Added by Jarl 2012-10-15, lets the callee handle its exit
		switchState();
		// Call the current state's entry function.
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
State* StateManager::getGameOverState()
{
	return m_gameOverState;
}
State* StateManager::getVictoryState()
{
	return m_victoryState;
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

void StateManager::stopMainTimer()
{
	m_timer->stop();
}

void StateManager::startMainTimer()
{
	m_timer->start();
}

CommonResources* StateManager::getCommonResources()
{
	return &m_commonResources;
}
int StateManager::readUnlockedMaps()
{
	ifstream file;
	file.open("../Maps/unlocked.txt", ios::in);
	if (file.is_open())
	{
		int unl;
		file >> unl;
		file.close();
		return unl;
	}
	return 0;
}
void StateManager::writeUnlockedMaps(int p_value)
{
	ofstream file;
	file.open("../Maps/unlocked.txt", ios::out);
	if (file.is_open())
	{
		file << p_value;
		file.close();
	}
}
