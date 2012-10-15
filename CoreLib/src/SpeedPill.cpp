#include "SpeedPill.h"

SpeedPill::SpeedPill(SpriteInfo* p_spriteInfo, Tile* p_tile, GameStats* p_gameStats, SoundInfo* p_onUseSound): Collectable(p_spriteInfo, p_gameStats)
{
	m_tile = p_tile;
	if (m_tile)
		m_tile->addPill(this);
	m_consumed = false;

	m_eatenStaten = new SpeedPillUse(this,p_onUseSound);
}
void SpeedPill::update(float p_deltaTime, InputInfo p_inputInfo)
{
}
void SpeedPill::consume()
{
	if (!m_consumed)
	{
		m_consumed = true;
		m_tile = NULL;
		m_gameStats->setSpeeded();

		switchState(m_eatenStaten);
	}
}