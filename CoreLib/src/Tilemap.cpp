#include "Tilemap.h"

Tilemap::Tilemap(int p_width, int p_height, Tile** p_tiles)
{
	m_width = p_width;
	m_height = p_height;
	m_tiles = p_tiles;
}
Tilemap::~Tilemap()
{
	for (int i = 0; i < m_width * m_height; i++)
	{
		delete m_tiles[i];
	}
	delete[] m_tiles;
}
Tile* Tilemap::getTile(TilePosition p_position)
{
	if (!isValidPosition(p_position))
		return NULL;

	return m_tiles[p_position.y * m_width + p_position.x];
}
Tile* Tilemap::closestFreeTile(Tile* p_start)
{
	TilePosition min = p_start->getTilePosition() - TilePosition(1, 1);
	TilePosition max = p_start->getTilePosition() + TilePosition(1, 1);

	while (min.x >= 0 || min.y >= 0 || max.x < m_width || max.y < m_height)
	{
		for (int row = min.y; row <= max.y; row++)
		{
			for (int col = min.x; col <= max.x; col++)
			{
				if (row == min.y || row == max.y || col == min.x || col == max.x)
				{
					Tile* t = getTile(TilePosition(col, row));
					if (t && t->isFree())
						return t;
				}
			}
		}
		min = min - TilePosition(1, 1);
		max = max + TilePosition(1, 1);
	}
	return 0;
}
bool Tilemap::isValidPosition(TilePosition p_position)
{
	if (p_position.x < 0 || p_position.x >= m_width)
		return false;
	if (p_position.y < 0 || p_position.y >= m_height)
		return false;
	return true;
}
int Tilemap::getWidth()
{
	return m_width;
}
int Tilemap::getHeight()
{
	return m_height;
}