#ifndef GAMESTATS_H
#define GAMESTATS_H

#include <Timer.h>
#include <vector>

using namespace std;

class GameStats
{
private:
	int				m_numPills;
	bool			m_speeded;
	bool			m_superMode;
	Timer*			m_timer;
	Timer*			m_superModeTimer;
	vector<Timer*>	m_powerUpTimers;
public:
	GameStats(Timer* p_timer);
	~GameStats();
	void	update(float p_deltaTime);
	void	setNumPills(const int p_numPills);
	int		getNumPills();
	void	pillEaten();
	void	addPill();
	void	setSpeeded();
	bool	isSpeeded();
	void	setSuperMode();
	bool	isSuperMode();
};

#endif