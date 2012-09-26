#include "Monster.h"

Monster::Monster(Tile* p_tile, Tilemap* p_map, SpriteInfo* p_spriteInfo): GameObject(p_spriteInfo)
{
	dt = 0;
	m_currentTile = p_tile;
	m_map = p_map;
	findNextTile();
	if (p_spriteInfo)
	{
		TilePosition tp = m_currentTile->getTilePosition();
		float w = m_currentTile->getWidth();
		float h = m_currentTile->getHeight();
		p_spriteInfo->transformInfo.translation[TransformInfo::X] = tp.x * w + w * 0.5f;
		p_spriteInfo->transformInfo.translation[TransformInfo::Y] = tp.y * h + h * 0.5f;
		p_spriteInfo->transformInfo.scale[TransformInfo::X] = w * 0.6f;
		p_spriteInfo->transformInfo.scale[TransformInfo::Y] = h * 0.6f;
	}
}
void Monster::update(float p_deltaTime, InputInfo p_inputInfo)
{
	dt += p_deltaTime*5;
	if (dt > 1)
	{
		dt -= 1;
		m_currentTile = m_nextTile;
		findNextTile();
	}
	TilePosition tp1 = m_currentTile->getTilePosition();
	TilePosition tp2 = m_nextTile->getTilePosition();
	float pX = tp1.x * (1-dt) + tp2.x * dt; 
	float pY = tp1.y * (1-dt) + tp2.y * dt;  

	float w = m_currentTile->getWidth();
	float h = m_currentTile->getHeight();
	m_spriteInfo->transformInfo.translation[TransformInfo::X] = pX * w + w * 0.5f;
	m_spriteInfo->transformInfo.translation[TransformInfo::Y] = pY * h + h * 0.5f;
}
Tile* Monster::getCurrentTile()
{
	return m_currentTile;
}
void Monster::findNextTile()
{
	if (m_map->isValidPosition(m_currentTile->getTilePosition() + TilePosition(-1, 0)))
	{
		Tile* t = m_map->getTile(m_currentTile->getTilePosition() + TilePosition(-1, 0));
		if (t->isFree())
		{
			m_nextTile = m_map->getTile(m_currentTile->getTilePosition() + TilePosition(-1, 0));
			return;
		}
	}
	if (m_map->isValidPosition(m_currentTile->getTilePosition() + TilePosition(0, 1)))
	{
		Tile* t = m_map->getTile(m_currentTile->getTilePosition() + TilePosition(0, 1));
		if (t->isFree())
		{
			m_nextTile = m_map->getTile(m_currentTile->getTilePosition() + TilePosition(0, 1));
			return;
		}
	}
	if (m_map->isValidPosition(m_currentTile->getTilePosition() + TilePosition(0, -1)))
	{
		Tile* t = m_map->getTile(m_currentTile->getTilePosition() + TilePosition(0, -1));
		if (t->isFree())
		{
			m_nextTile = m_map->getTile(m_currentTile->getTilePosition() + TilePosition(0, -1));
			return;
		}
	}
	if (m_map->isValidPosition(m_currentTile->getTilePosition() + TilePosition(1, 0)))
	{
		Tile* t = m_map->getTile(m_currentTile->getTilePosition() + TilePosition(1, 0));
		if (t->isFree())
		{
			m_nextTile = m_map->getTile(m_currentTile->getTilePosition() + TilePosition(1, 0));
			return;
		}
	}
}