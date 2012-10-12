#ifndef AVATAR_H
#define AVATAR_H

#include "Tilemap.h"

class AvatarKilled;

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

	AvatarKilled* m_avatarKilledState;

	float dt;
private:
	void checkInput(InputInfo p_inputInfo);
	bool check180();

public:
	Avatar(SpriteInfo* p_spriteInfo, Tilemap* p_map, Tile* p_startTile, GameStats* p_stats, SoundInfo* p_avatarKilledSound);
	virtual ~Avatar();
	void	update(float p_deltaTime, InputInfo p_inputInfo);

	Tile*		getCurrentTile();
	int			getDirection();
	float		getTileInterpolationFactor();
	void		setTilePosition(Tile* p_newPosition);
	void		kill();
};

#endif