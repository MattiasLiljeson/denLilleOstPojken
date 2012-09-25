#ifndef TILE_H
#define TILE_H

#include "GameObject.h"

struct TilePosition
{
	int x;
	int y;

	TilePosition()
	{
		x = 0;
		y = 0;
	}
	TilePosition(int p_x, int p_y)
	{
		x = p_x;
		y = p_y;
	}
	TilePosition& operator-(const TilePosition& p_other)
	{
		x -= p_other.x;
		y -= p_other.y;
		return (*this);
	}
	TilePosition& operator+(const TilePosition& p_other)
	{
		x += p_other.x;
		y += p_other.y;
		return (*this);
	}
};

enum TileType
{
	FREE_TILE,
	WALL_TILE,
	SPAWN_PILL
};

class Tile: public GameObject
{
private:
	TileType		m_type;
	TilePosition	m_position;
	float			m_width;
	float			m_height;
public:
	Tile(TileType p_type, TilePosition p_position, float p_width, float p_height, SpriteInfo* p_spriteInfo);
	TileType getType();
	TilePosition getPosition();
	float getWidth();
	float getHeight();
	bool isFree();
};

#endif