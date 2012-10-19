#ifndef GAMESTATS_H
#define GAMESTATS_H

#include <Timer.h>
#include <vector>
#include <InputInfo.h>

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
	int				m_lives;

	int				m_itemSlot;
	int				m_buffSlot;

	//Flag to indicate the spawn of an item
	int				m_activate;
public:
	GameStats(Timer* p_timer);
	~GameStats();
	void	update(float p_deltaTime, InputInfo p_inputInfo);
	void	setNumPills(const int p_numPills);
	int		getNumPills();
	int		getNumLives();
	void	pillEaten();
	void	addPill();
	void	setSpeeded();
	bool	isSpeeded();
	void	setSuperMode();
	bool	isSuperMode();
	float   superTimeRemaining();
	float	speededPercentElapsed();
	void	addScore(int p_points);
	int		getScore() const;
	Timer*	getGameTimer();
	void	loseLife();
	void	setItemSlot(int p_item);
	int		getItemSlot();
	void	setBuffSlot(int p_buff);
	int		getBuffSlot();
	void	activateBuff();
	void	activateItem();
	int		getActivatedItem();
	void	clearBuffs();
};

#endif