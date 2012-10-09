#include "Switch.h"

Switch::Switch(SpriteInfo* p_spriteInfo, Tile* p_tile, Tilemap* p_map, GameStats* p_gameStats, vector<TilePosition> p_targets): Collectable(p_spriteInfo, p_gameStats)
{
	m_map = p_map;

	m_targets = p_targets;

	m_tile = p_tile;
	m_tile->addPill(this);
	m_consumed = false;
	m_cooldown = 0;
}
void Switch::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if (m_cooldown == 0)
	{
		m_spriteInfo->visible = true;
	}
	else if (m_cooldown > 0)
	{
		m_spriteInfo->visible = false;
	}
	m_cooldown = max(m_cooldown - p_deltaTime, 0.0f);
}
void Switch::consume()
{
	if (m_cooldown <= 0)
	{
		for (unsigned int i = 0; i < m_targets.size(); i++)
		{
			Tile* t = m_map->getTile(m_targets[i]);
			t->switchState();
		}
		m_cooldown = 5;
	}
}