#ifndef TILE_H
#define TILE_H

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
	WALL_TILE
};

class Tile
{
private:
	TileType		m_type;
	TilePosition	m_position;
public:
	Tile(TileType p_type, TilePosition p_position);
	TileType getType();
	TilePosition getPosition();
	bool isFree();
};

#endif