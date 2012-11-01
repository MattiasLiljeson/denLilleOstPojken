#ifndef MONSTER_H
#define MONSTER_H


#ifndef _WIN32
#include <math.h>
#include <time.h>
#include <stdlib.h>
#endif

#include "Tilemap.h"
#include "Avatar.h"
#include "AI.h"
#include "Animation.h"

struct AstarItem
{
	Tile* tile;
	int parent;
	int toStart;
	int toGoal;
	int distance()
	{
		return toStart + toGoal;
	}
};

class Monster: public GameObject
{
protected:
	Tile*		m_currentTile;
	Tile*		m_nextTile;
	Tilemap*	m_map;
	Tile*		m_startMap;
	Tile*		m_startTile;

	AI* m_ai;

	//temp
	float dt;

	vector<Tile*> m_path;

	Animation* m_left;
	Animation* m_right;
	Animation* m_up;
	Animation* m_down;

	Animation* m_currentAnimation;

	bool	m_dead;
	bool	m_respawning;
	SoundInfo* m_monsterKilledSound;
protected:
	Monster(GameStats* p_gameStats, SpriteInfo* p_spriteInfo);
protected:
	int		UpdateQueue(Tile* p_tile, int p_parent, int p_toStart, int p_toGoal,
				vector<AstarItem>& p_queue);
	int		FindTile(Tile* p_tile, vector<AstarItem>& p_queue);
	void	determineAnimation();
	void	transformSpriteInformation();
public:
	virtual ~Monster();
	virtual void	update(float p_deltaTime, InputInfo p_inputInfo) = 0;
	Tile*	getCurrentTile();
	void	FindPath(Tile* p_start, Tile* p_goal);
	void	kill();
	bool	isDead();
	void	addMonsterAI(Avatar* p_avatar, GameStats* p_gameStats, Tilemap* p_tilemap);
	virtual void	reset();
	virtual void	beginRespawn();
	void	respawn();
};

#endif
