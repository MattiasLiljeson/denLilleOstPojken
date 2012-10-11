#ifndef GAMESTATS_H
#define GAMESTATS_H

#include <Timer.h>
#include <vector>

using namespace std;

enum
{
	MONSTER_KILLED = 100, PILL_EATEN = 10
};

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
	int		getScore() const;
	Timer*	getGameTimer();
};

#endif