#include "Tile.h"

Tile::Tile(TileType p_type, TilePosition p_position)
{
	m_position = p_position;
	m_type = p_type;
}
TileType Tile::getType()
{
	return m_type;
}
TilePosition Tile::getPosition()
{
	return m_position;
}
bool Tile::isFree()
{
	return m_type != TileType::WALL_TILE; 
}