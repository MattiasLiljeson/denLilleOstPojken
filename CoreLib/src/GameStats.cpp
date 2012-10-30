#include "GameStats.h"
#include <iostream>
#include "Monster.h"
#include "Collectable.h"

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
	m_itemSlot	= NULL;
	m_buffSlot	= NULL;
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

	for(unsigned int i = 0; i < m_monstersRespawnTimers.size(); i++)
		delete m_monstersRespawnTimers.at(i).second;
}

void GameStats::update(float p_deltaTime, InputInfo p_inputInfo)
{
	m_activate = -1;
	m_timer->tick();

	for(unsigned int index = 0; index<m_powerUpTimers.size(); index++)
	{
		if (p_deltaTime > 0)
		{
			if (m_powerUpTimers[index]->isPaused())
				m_powerUpTimers[index]->start();
			m_powerUpTimers.at(index)->tick();
		}
		else
			m_powerUpTimers[index]->pause();
	}
	for(unsigned int index = 0; index < m_monstersRespawnTimers.size(); index++)
	{
		Timer* timer = m_monstersRespawnTimers[index].second;
		Monster* monster = m_monstersRespawnTimers[index].first;

		if(p_deltaTime > 0)
			timer->tick();

		if(timer->getElapsedTime() >= MONSTER_BEGINRESPAWN)
			monster->beginRespawn();
		if(timer->getElapsedTime() >= MONSTER_RESPAWNTIME)
		{
			monster->respawn();
			timer = NULL;
			delete m_monstersRespawnTimers[index].second;
			m_monstersRespawnTimers[index] = m_monstersRespawnTimers.back();
			m_monstersRespawnTimers.pop_back();
		}
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
	return (float)( 6 - m_superModeTimer->getElapsedTime() );
}
float GameStats::speededPercentElapsed()
{
	return (float)( m_speedUpTimer->getElapsedTime() / 3.0f );
}
void GameStats::addScore(int p_points)
{
	m_score += p_points;
}
int GameStats::getScore() const
{
	return m_score;
}
int	GameStats::getTotalScore()
{
	return (int)( m_previousScore + m_score * getMultiplier() );
}
Timer* GameStats::getGameTimer()
{
	return m_gameTimer;
}
void GameStats::loseLife()
{
	m_lives = max(0, m_lives-1);
}
void GameStats::setItemSlot(Collectable* p_item)
{
	m_itemSlot = p_item;
}
Collectable* GameStats::getItemSlot()
{
	return m_itemSlot;
}
void GameStats::setBuffSlot(Collectable* p_buff)
{
	m_buffSlot = p_buff;
}
Collectable* GameStats::getBuffSlot()
{
	return m_buffSlot;
}
void GameStats::activateBuff()
{
	if (m_buffSlot != NULL && !m_speeded)
	{
		m_buffSlot->activate();
		setSpeeded();
		m_buffSlot = NULL;
	}
}
void GameStats::activateItem()
{
	if(m_itemSlot != NULL)
	{
		m_activate = 0;
		m_itemSlot->activate();
		m_itemSlot = NULL;
	}
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
float GameStats::getMultiplier()
{
	float t = (float)m_gameTimer->getElapsedTime();
	if (t > m_parTime)
		return 1;
	float frac = 1-(t / m_parTime);
	return 1 + frac;
}
void GameStats::halvePreviousScore()
{
	m_previousScore /= 2;
//	m_previousScore *= 0.5f;
}
int	GameStats::getPreviousScore()
{
	return m_previousScore;
}
void GameStats::monsterKilled(Monster* p_monster)
{
	pair<Monster*, Timer*> newPair(p_monster,m_timer->newInstance());
	newPair.second->start();
	m_monstersRespawnTimers.push_back(newPair);
};

float GameStats::getTimeUntilMonsterRespawn(Monster* p_monster)
{
	for(unsigned int i = 0;i < m_monstersRespawnTimers.size(); i++)
	{
		if (m_monstersRespawnTimers[i].first == p_monster)
		{
			float timeLeft =
				(float)(m_monstersRespawnTimers[i].second->getElapsedTime() -
				MONSTER_RESPAWNTIME);

			return timeLeft;
		}
	}

	return 0;
}