#include "Tile.h"

Tile::Tile(TileType p_type, TilePosition p_position, float p_width, float p_height, SpriteInfo* p_spriteInfo): GameObject(p_spriteInfo)
{
	m_width = p_width;
	m_height = p_height;
	if (p_spriteInfo)
	{
		p_spriteInfo->transformInfo.translation[TransformInfo::X] = p_position.x * p_width + p_width * 0.5f;
		p_spriteInfo->transformInfo.translation[TransformInfo::Y] = p_position.y * p_height + p_height * 0.5f;
		p_spriteInfo->transformInfo.scale[TransformInfo::X] = p_width;
		p_spriteInfo->transformInfo.scale[TransformInfo::Y] = p_height;
	}
	m_position = p_position;
	m_type = p_type;
}
TileType Tile::getType()
{
	return m_type;
}
fVector2 Tile::getPosition()
{
	return fVector2(m_position.x * m_width + m_width * 0.5f, m_position.y * m_height + m_height * 0.5f);
}
TilePosition Tile::getTilePosition()
{
	return m_position;
}
float Tile::getWidth()
{
	return m_width;
}
float Tile::getHeight()
{
	return m_height;
}
bool Tile::isFree()
{
	return m_type != TileType::WALL_TILE; 
}