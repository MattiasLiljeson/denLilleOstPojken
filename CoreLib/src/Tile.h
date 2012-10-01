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

class Tile: public GameObject
{
private:
	bool			m_type;
	TilePosition	m_position;
	float			m_width;
	float			m_height;

	Pill*			m_pill;

public:
	Tile(bool p_type, TilePosition p_position, float p_width, float p_height, SpriteInfo* p_spriteInfo);
	bool getType();
	TilePosition getTilePosition();
	fVector2		getPosition();
	float getWidth();
	float getHeight();
	bool isFree();
	void addPill(Pill* p_pill);
	bool removePill();
};

#endif