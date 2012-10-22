#include "GameStats.h"
#include <iostream>


GameStats::GameStats(Timer* p_timer, int p_parTime, int p_previousScore)
{
	m_timer		= p_timer;
	m_parTime	= p_parTime;
	m_numPills	= 0;
	m_speeded	= false;
	m_superMode = false;
	m_score		= 0;
	m_previousScore = p_previousScore;
	m_lives		= 3;
	m_itemSlot	= -1;
	m_buffSlot	= -1;
	m_activate = -1;

	m_gameTimer = m_superModeTimer = m_speedUpTimer = NULL;

	if(p_timer)
	{
		m_gameTimer = m_timer->newInstance();
		m_gameTimer->start();

		m_superModeTimer = m_timer->newInstance();
		m_speedUpTimer = m_timer->newInstance();

		m_powerUpTimers.push_back(m_superModeTimer);
		m_powerUpTimers.push_back(m_speedUpTimer);
		m_powerUpTimers.push_back(m_gameTimer);
	}
}

GameStats::~GameStats()
{
	delete m_timer;

	for(unsigned int i = 0; i < m_powerUpTimers.size(); i++)
		delete m_powerUpTimers.at(i);
}

void GameStats::update(float p_deltaTime, InputInfo p_inputInfo)
{
	m_activate = -1;
	m_timer->tick();

	for(int unsigned index = 0; index<m_powerUpTimers.size(); index++)
	{
		m_powerUpTimers.at(index)->tick();
	}

	if(m_superMode)
	{
		if(m_superModeTimer->getElapsedTime() > 6)
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

	if (p_inputInfo.keys[InputInfo::X_KEY] == InputInfo::KEYPRESSED)
		activateBuff();
	if (p_inputInfo.keys[InputInfo::Z_KEY] == InputInfo::KEYPRESSED)
		activateItem();
}

void GameStats::setNumPills(const int p_numPills)
{
	m_numPills = p_numPills;
}
int	GameStats::getNumLives()
{
	return m_lives;
}

int GameStats::getNumPills()
{
	return m_numPills;
}

void GameStats::pillEaten()
{
	m_numPills -= 1;
	addScore(PILL_EATEN);
}
void GameStats::addPill()
{
	m_numPills += 1;
}
void GameStats::setSpeeded()
{
	m_speeded = true;
	if (m_speedUpTimer)
		m_speedUpTimer->start();
}
bool GameStats::isSpeeded()
{
	return m_speeded;
}
void GameStats::setSuperMode()
{
	m_superMode = true;
	if (m_superModeTimer)
		m_superModeTimer->start();
}
bool GameStats::isSuperMode()
{
	return m_superMode;
}
float GameStats::superTimeRemaining()
{
	return 6 - m_superModeTimer->getElapsedTime();
}
float GameStats::speededPercentElapsed()
{
	return m_speedUpTimer->getElapsedTime() / 3.0f;
}
void GameStats::addScore(int p_points)
{
	m_score += p_points;
}
int GameStats::getScore() const
{
	return m_score;
}
int	GameStats::getTotalScore() const
{
	return m_previousScore + m_score;
}
Timer* GameStats::getGameTimer()
{
	return m_gameTimer;
}
void GameStats::loseLife()
{
	m_lives = max(0, m_lives-1);
}
void	GameStats::setItemSlot(int p_item)
{
	m_itemSlot = p_item;
}
int		GameStats::getItemSlot()
{
	return m_itemSlot;
}
void	GameStats::setBuffSlot(int p_buff)
{
	m_buffSlot = p_buff;
}
int		GameStats::getBuffSlot()
{
	return m_buffSlot;
}
void	GameStats::activateBuff()
{
	if (m_buffSlot == 0)
		setSpeeded();
	m_buffSlot = -1;
}
void	GameStats::activateItem()
{
	m_activate = m_itemSlot;
	m_itemSlot = -1;
}
int GameStats::getActivatedItem()
{
	return m_activate;
}
void GameStats::clearBuffs()
{
	m_speeded	 = false;
	m_superMode	 = false;
	m_superModeTimer->stop();
	m_speedUpTimer->stop();
}
int GameStats::getParTime()
{
	return m_parTime;
}