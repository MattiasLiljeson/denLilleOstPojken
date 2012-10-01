#ifndef TILE_H
#define TILE_H

#include "GameObject.h"
#include <Vector2.h>

class Pill;

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
	TilePosition operator-(const TilePosition& p_other)
	{
		int nx = x - p_other.x;
		int ny = y - p_other.y;
		return TilePosition(nx, ny);
	}
	TilePosition operator+(const TilePosition& p_other)
	{
		int nx = x + p_other.x;
		int ny = y + p_other.y;
		return TilePosition(nx, ny);
	}
};

enum TileType
{
	EMPTY,
	WALL_CENTER,
	PILL,
	AVATAR_SPAWN,
	MONSTER_SPAWN
};

class Tile: public GameObject
{
private:
	TileType		m_type;
	TilePosition	m_position;
	float			m_width;
	float			m_height;

	Pill* m_pill;

public:
	Tile(TileType p_type, TilePosition p_position, float p_width, float p_height, SpriteInfo* p_spriteInfo);
	TileType getType();
	TilePosition getTilePosition();
	fVector2		getPosition();
	float getWidth();
	float getHeight();
	bool isFree();
	void addPill(Pill* p_pill);
	void removePill();
};

#endif