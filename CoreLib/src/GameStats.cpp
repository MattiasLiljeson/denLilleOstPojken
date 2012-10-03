#include "GameStats.h"
#include <iostream>


GameStats::GameStats()
{
}
GameStats::GameStats(Timer* p_timer)
{
	m_timer = p_timer;

	m_numPills = 0;
	m_speeded = false;
	m_superMode = false;

	m_gameTimer = m_timer->newInstance();
	m_gameTimer->start();

	m_superModeTimer = m_timer->newInstance();
	m_speedUpTimer = m_timer->newInstance();

	m_powerUpTimers.push_back(m_superModeTimer);
	m_powerUpTimers.push_back(m_speedUpTimer);
	m_powerUpTimers.push_back(m_gameTimer);
}

GameStats::~GameStats()
{
	delete m_timer;

	while (!m_powerUpTimers.empty())
	{
		Timer* tempTimer = m_powerUpTimers.back();
		m_powerUpTimers.pop_back();
		delete tempTimer;
	}
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
		if(m_superModeTimer->getElapsedTime() > 3)
		{
			std::cout << "Speed mode inactivated!=(" << std::endl;
			m_superMode = false;
			m_superModeTimer->stop();
		}
	}
	if (m_speeded)
	{
		if (m_speedUpTimer->getElapsedTime() > 3)
		{
			std::cout << "Speed mode inactivated!=((" << std::endl;
			m_speeded = false;
			m_speedUpTimer->stop();
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
	std::cout << "Speed mode activated!=)" << std::endl;
	m_speeded = true;
	m_speedUpTimer->start();
}
bool GameStats::isSpeeded()
{
	return m_speeded;
}
void GameStats::setSuperMode()
{
	std::cout << "Super mode activated!=))" << std::endl;
	m_superMode = true;
	m_superModeTimer->start();
}
bool GameStats::isSuperMode()
{
	return m_superMode;
}
float GameStats::superTimeRemaining()
{
	return 3 - m_superModeTimer->getElapsedTime();
}
void GameStats::addScore(int p_points)
{
	m_score += p_points;
}
Timer* GameStats::getGameTimer()
{
	return m_gameTimer;
}