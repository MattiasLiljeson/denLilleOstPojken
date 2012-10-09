#include "Pill.h"

Pill::Pill(SpriteInfo* p_spriteInfo, Tile* p_tile, GameStats* p_gameStats): Collectable(p_spriteInfo, p_gameStats)
{
	p_gameStats->addPill();
	m_tile = p_tile;
	m_tile->addPill(this);
	m_consumed = false;
}
void Pill::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if (m_consumed)
	{
		m_spriteInfo->visible = false;
	}
}
void Pill::consume()
{
	if (!m_consumed)
	{
		m_consumed = true;
		m_tile = NULL;
		m_gameStats->pillEaten();
	}
}