#include "Switch.h"

Switch::Switch(SpriteInfo* p_spriteInfo, Tile* p_tile, GameStats* p_gameStats, vector<WallSwitch*>* p_targets): Collectable(p_spriteInfo, p_gameStats)
{
	m_targets = p_targets;

	m_tile = p_tile;
	if (m_tile)
		m_tile->addPill(this);
	m_consumed = false;
	m_cooldown = 0;
}
Switch::~Switch()
{
}
void Switch::setTargets(vector<WallSwitch*>* p_targets)
{
	m_targets = p_targets;
}
void Switch::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if (m_cooldown == 0)
	{
		//m_spriteInfo->visible = true;
		m_spriteInfo->textureRect.x = 0;
	}
	else if (m_cooldown > 0)
	{
		//m_spriteInfo->visible = false;
		m_spriteInfo->textureRect.x = 64;
	}
	m_cooldown = max(m_cooldown - p_deltaTime, 0.0f);
}
void Switch::consume()
{
	if (m_cooldown <= 0)
	{
		for (unsigned int i = 0; i < m_targets->size(); i++)
		{
			m_targets->at(i)->switchState();
		}
		m_cooldown = 5;
	}
}