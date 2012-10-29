#ifndef GAMESTATS_H
#define GAMESTATS_H

#include <Timer.h>
#include <vector>
#include <InputInfo.h>

class Monster;

using namespace std;

enum
{
	MONSTER_KILLED = 100, PILL_EATEN = 10
};

const static int MONSTER_BEGINRESPAWN = 10;
const static int MONSTER_RESPAWNTIME = 12;

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
	vector<pair<Monster*, Timer*>>	m_monstersRespawnTimers;
	int				m_score;
	int				m_previousScore;
	int				m_lives;

	int				m_parTime;
	int				m_itemSlot;
	int				m_buffSlot;

	//Flag to indicate the spawn of an item
	int				m_activate;

public:
	GameStats(Timer* p_timer, int p_parTime, int p_previousScore = 0);
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
	int		getTotalScore();
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
	int		getParTime();
	float	getMultiplier();
	void	halvePreviousScore();
	int		getPreviousScore();
	void	monsterKilled(Monster*);
	float	getTimeUntilMonsterRespawn(Monster*);
};

#endif