#include "GameStats.h"

GameStats::GameStats()
{
	m_numPills = 0;
}

GameStats::~GameStats()
{

}

void GameStats::update(float p_deltaTime)
{

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
	std::cout<<m_numPills<<std::endl;
}