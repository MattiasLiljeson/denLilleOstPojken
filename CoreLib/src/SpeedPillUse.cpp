#include "SpeedPillUse.h"

SpeedPillUse::SpeedPillUse(GameObject* p_gameObject, SoundInfo* p_onEatSound) : GOState (p_gameObject)
{
	m_onUseSound = p_onEatSound;
}

SpeedPillUse::~SpeedPillUse()
{
}

int SpeedPillUse::onEnter()
{
	m_onUseSound->play = true;
	m_gameObject->getSpriteInfo()->visible = false;
	return GAME_OK;
}

int SpeedPillUse::onExit()
{
	return GAME_OK;
}

int SpeedPillUse::update(float p_dt, InputInfo p_inputInfo)
{
	return GAME_OK;
}