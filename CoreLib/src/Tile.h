#ifndef TILE_H
#define TILE_H

#include "Collectable.h"
#include <fVector2.h>
#include "IODevice.h"

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
	bool operator==(const TilePosition& p_other)
	{
		return x == p_other.x && y == p_other.y;
	}
};

class Tile: public GameObject
{
private:
	bool			m_type;
	TilePosition	m_position;
	float			m_width;
	float			m_height;

	Collectable*	m_collectable;
	IODevice* m_io;

public:
	Tile(bool p_type, TilePosition p_position, float p_width, float p_height, SpriteInfo* p_spriteInfo);
	~Tile();
	bool getType();
	TilePosition getTilePosition();
	fVector2		getPosition();
	float getWidth();
	float getHeight();
	bool isFree();
	void addPill(Collectable* p_pill);
	bool removePill();
	void switchState();
	void setWalkAble(bool p_walkAble);
};

#endif