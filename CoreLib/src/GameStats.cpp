#include "GameStats.h"

GameStats::GameStats(Timer* p_timer)
{
	m_timer = p_timer;

	m_numPills = 0;
	m_speeded = false;
	m_superMode = false;
	m_superModeTimer = m_timer->newInstance();

	m_powerUpTimers.push_back(m_superModeTimer);
}

GameStats::~GameStats()
{
	delete m_timer;
}

void GameStats::update(float p_deltaTime)
{
	m_timer->tick();

	for(int unsigned index = 0; index<m_powerUpTimers.size(); index++)
	{
		m_powerUpTimers.at(index)->tick();
	}

	if(m_superMode)
	{
		if(m_superModeTimer->getElapsedTime()>3)
		{
			m_superMode = false;
			m_superModeTimer->stop();
		}
	}
}

void GameStats::setNumPills(const int p_numPills)
{
	m_numPills = p_numPills;
}

int GameStats::getNumPills()
{
	return m_numPills;
}

void GameStats::pillEaten()
{
	m_numPills -= 1;
}
void GameStats::addPill()
{
	m_numPills += 1;
}
void GameStats::setSpeeded()
{
	m_speeded = true;
}
bool GameStats::isSpeeded()
{
	return m_speeded;
}
void GameStats::setSuperMode()
{
	m_superMode = true;
	m_superModeTimer->start();
}
bool GameStats::isSuperMode()
{
	return m_superMode;
}