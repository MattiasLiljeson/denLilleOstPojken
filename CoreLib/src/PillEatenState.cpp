#include "PillEatenState.h"

PillEatenState::PillEatenState(GameObject* p_gameObject, SpriteInfo* p_spriteInfo) : GOState(p_gameObject)
{
	m_spriteInfo = p_spriteInfo;
}
int PillEatenState::onEnter()
{
	//Consume the pill upon entry
	Pill* p = (Pill*)m_gameObject;
	p->consume();
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