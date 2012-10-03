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
	int m_desired;

	float dt;

	IODevice* m_io;
private:
	void checkInput(InputInfo p_inputInfo);

public:
	Avatar(IODevice* p_io, Tilemap* p_map, Tile* p_startTile, GameStats* p_stats);

	void	update(float p_deltaTime, InputInfo p_inputInfo);

	Tile*	getCurrentTile();
	int		getDirection();
	float	getTileInterpolationFactor();
	void	setTilePosition(Tile* p_newPosition);
};

#endif