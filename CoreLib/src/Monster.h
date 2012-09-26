#ifndef MONSTER_H
#define MONSTER_H

#include "Tilemap.h"

class Monster: public GameObject
{
private:
	Tile* m_currentTile;
	Tile* m_nextTile;
	Tilemap* m_map;

	//temp
	float dt;

private:
	void findNextTile();

public:
	Monster(Tile* p_tile, Tilemap* p_map, SpriteInfo* p_spriteInfo);
	void update(float p_deltaTime, InputInfo p_inputInfo);
	Tile* getCurrentTile();
};

#endif