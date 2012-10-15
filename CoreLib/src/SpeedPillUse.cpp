#include "SpeedPillUse.h"

SpeedPillUse::SpeedPillUse(GameObject* p_gameObject, SoundInfo* p_onEatSound) : GOState (p_gameObject)
{
	m_onUseSound = p_onEatSound;
}

SpeedPillUse::~SpeedPillUse()
{
	if(m_onUseSound)
		delete m_onUseSound;
}

int SpeedPillUse::onEnter()
{
	if (m_onUseSound)
		m_onUseSound->play = true;
	if (m_gameObject->getSpriteInfo())
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