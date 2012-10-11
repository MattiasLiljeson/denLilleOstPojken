#include "PillIdleState.h"

PillIdleState::PillIdleState(GameObject* p_gameObject, SpriteInfo* p_spriteInfo): GOState(p_gameObject)
{
	m_spriteInfo = p_spriteInfo;
}
int PillIdleState::onEnter()
{
	return GAME_OK;
}
int PillIdleState::onExit()
{
	return GAME_OK;
}
int PillIdleState::update(float p_dt, InputInfo p_inputInfo)
{
	return GAME_OK;
}