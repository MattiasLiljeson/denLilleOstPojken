#ifndef AI_H
#define AI_H

#include "Avatar.h"
#include "Tile.h"
#include "GameStats.h"
#include "Tilemap.h"
#include <fVector2.h>

class Monster;

class AI
{
private:
	Monster*	m_master;
	Avatar*		m_avatar;
	GameStats*	m_gameStats;
	Tilemap*	m_tilemap;
	float		m_elapsedTime;
public:
	AI(Monster* p_master, Avatar* p_avatar, GameStats* p_gameStats, Tilemap* p_tilemap);
	~AI();
	void update(float p_deltaTime);
	void findTarget();
	bool shouldChaseTarget();
	void chaseTarget();
	void fleeFromTarget();
	bool randBool();
	bool seesTarget();
	Tile* findRushTile();
};

#endif