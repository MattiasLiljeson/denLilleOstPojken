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
private:
	Tile*		m_currentTile;
	Tile*		m_nextTile;
	Tilemap*	m_map;
	Tile*		m_startMap;

	AI* m_ai;

	//temp
	float dt;

	vector<Tile*> m_path;

	Animation* m_left;
	Animation* m_right;
	Animation* m_up;
	Animation* m_down;

	Animation* m_currentAnimation;

	bool m_dead;
private:
	int		UpdateQueue(Tile* p_tile, int p_parent, int p_toStart, int p_toGoal,
				vector<AstarItem>& p_queue);
	int		FindTile(Tile* p_tile, vector<AstarItem>& p_queue);
	void	determineAnimation();
public:
	Monster(SpriteInfo* p_spriteInfo, Tile* p_tile, Tilemap* p_map);
	~Monster();
	void	update(float p_deltaTime, InputInfo p_inputInfo);
	Tile*	getCurrentTile();
	void	FindPath(Tile* p_start, Tile* p_goal);
	void	kill();
	bool	isDead();
	void	addMonsterAI(Avatar* p_avatar, GameStats* p_gameStats, Tilemap* p_tilemap);
};

#endif
