#ifndef AVATAR_H
#define AVATAR_H

#include "Tilemap.h"



struct Direction
{
	enum
	{
		LEFT, RIGHT, DOWN, UP, NONE
	};
};
static TilePosition Directions[4] = 
{
	TilePosition(-1,0), 
	TilePosition(1,0), 
	TilePosition(0,-1), 
	TilePosition(0,1)
};

class Avatar : public GameObject
{
private:
	Tile* m_currentTile;
	Tile* m_nextTile;
	Tile* m_queuedTile;
	Tilemap* m_map;

	int m_direction;

	float dt;
private:
	int checkInput(InputInfo p_inputInfo);

public:
	Avatar();
	Avatar(SpriteInfo* p_spriteInfo, Tilemap* p_map, Tile* p_startTile);

	void update(float p_deltaTime, InputInfo p_inputInfo);
};

#endif