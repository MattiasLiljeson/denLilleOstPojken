#include "BombPill.h"

BombPill::BombPill(SpriteInfo* p_spriteInfo, Tile* p_tile, GameStats* p_gameStats, SoundInfo* p_onUseSound): Collectable(p_spriteInfo, p_gameStats)
{
	m_tile = p_tile;
	if (m_tile)
		m_tile->addPill(this);
	m_consumed = false;
	m_onUseSound = p_onUseSound;
}
BombPill::~BombPill()
{
}
void BombPill::update(float p_deltaTime, InputInfo p_inputInfo)
{
}
void BombPill::consume()
{
	if (!m_consumed)
	{
		m_consumed = true;
		m_tile = NULL;
		m_gameStats->setItemSlot(0);
		m_onUseSound->play = true;
		m_spriteInfo->visible = false;
	}
}