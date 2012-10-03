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
	Timer*			m_speedUpTimer;
	Timer*			m_gameTimer;
	vector<Timer*>	m_powerUpTimers;
	int				m_score;
public:
	GameStats();
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
	float   superTimeRemaining();
	void	addScore(int p_points);
	Timer*	getGameTimer();
};

#endif