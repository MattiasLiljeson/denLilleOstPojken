#include "SuperPill.h"


SuperPill::SuperPill(SpriteInfo* p_spriteInfo, Tile* p_tile, GameStats* p_gameStats, SoundInfo* p_onEatSound) : Collectable(p_spriteInfo,p_gameStats)
{
	m_tile = p_tile;
	if (m_tile)
		m_tile->addPill(this);
	m_consumed = false;
	m_superPillEaten = new SuperPillEaten(this,p_onEatSound);
}

SuperPill::~SuperPill()
{
	if (m_superPillEaten)
		delete m_superPillEaten;
}

void SuperPill::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if(m_consumed)
	{
		if (m_spriteInfo)
			m_spriteInfo->visible = false;
	}
}

void SuperPill::consume()
{
	if(!m_consumed)
	{
		m_consumed = true;
		m_tile = NULL;
		m_gameStats->setSuperMode();

		switchState(m_superPillEaten);
	}
}