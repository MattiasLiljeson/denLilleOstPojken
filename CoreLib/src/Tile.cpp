#include "Tile.h"
#include "Pill.h"

Tile::Tile(bool p_type, TilePosition p_position, float p_width, float p_height, SpriteInfo* p_spriteInfo): GameObject(p_spriteInfo)
{
	m_width = p_width;
	m_height = p_height;

	m_position = p_position;
	m_type = p_type;
	m_collectable = NULL;
}
Tile::~Tile()
{
}
bool Tile::getType()
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
	return m_type; 
}
void Tile::addPill(Collectable* p_pill)
{
	m_collectable = p_pill;
}
bool Tile::removePill()
{
	if (m_collectable)
	{
		m_collectable->consume();
		if (m_collectable->isConsumed())
			m_collectable = NULL;
		return true;
	}
	return false;
}
void Tile::switchState()
{
	m_type = !m_type;
	if (m_type)
		m_spriteInfo->visible = false;
	else
		m_spriteInfo->visible = true;
}
void Tile::setWalkAble(bool p_walkAble)
{
	m_type = p_walkAble;
}