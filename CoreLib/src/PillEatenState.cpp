#include "PillEatenState.h"

PillEatenState::PillEatenState(GameObject* p_gameObject, SpriteInfo* p_spriteInfo, SoundInfo* p_onEatSound, GameStats* p_gameStats) : GOState(p_gameObject)
{
	m_spriteInfo = p_spriteInfo;
	m_onEatSound = p_onEatSound;
	m_gameStats = p_gameStats;
}
PillEatenState::~PillEatenState()
{
	if (m_onEatSound)
		m_onEatSound->deleted = true;
}
int PillEatenState::onEnter()
{
	//Consume the pill upon entry
	Pill* p = (Pill*)m_gameObject;
	m_gameStats->pillEaten();
	m_onEatSound->play = true;
	p->getSpriteInfo()->visible = false;

	return GAME_OK;
}
int PillEatenState::onExit()
{
	//Should never return to non-eaten state
	return GAME_FAIL;
}
int PillEatenState::update(float p_dt, InputInfo p_inputInfo)
{
	return GAME_OK;
}