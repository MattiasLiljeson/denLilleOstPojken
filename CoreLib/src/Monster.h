#ifndef MONSTER_H
#define MONSTER_H


#ifndef _WIN32
#include <math.h>
#include <time.h>
#include <stdlib.h>
#endif

#include "Tilemap.h"

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
	Tile* m_currentTile;
	Tile* m_nextTile;
	Tilemap* m_map;

	//temp
	float dt;

	vector<Tile*> m_path;

public:
	Monster(Tile* p_tile, Tilemap* p_map, SpriteInfo* p_spriteInfo);
	void update(float p_deltaTime, InputInfo p_inputInfo);
	Tile* getCurrentTile();
	void FindPath(Tile* p_start, Tile* p_goal);
	int	UpdateQueue(Tile* p_tile, int p_parent, int p_toStart, int p_toGoal, vector<AstarItem>& p_queue);
	int	FindTile(Tile* p_tile, vector<AstarItem>& p_queue);
};

#endif
