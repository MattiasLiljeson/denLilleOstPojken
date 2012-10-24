#include "SuperPillEaten.h"

SuperPillEaten::SuperPillEaten(GameObject* p_gameObject, SoundInfo* p_onEatSound): GOState(p_gameObject)
{
	m_onEatSound = p_onEatSound;
}
SuperPillEaten::~SuperPillEaten()
{
	if(m_onEatSound)
		m_onEatSound->deleted = true;
}
int SuperPillEaten::onEnter()
{
	if(m_gameObject->getSpriteInfo())
		m_gameObject->getSpriteInfo()->visible = false;
	
	if(m_onEatSound)
		m_onEatSound->play = true;

	return GAME_OK;
}
int SuperPillEaten::onExit()
{
	return GAME_OK;
}
int SuperPillEaten::update(float p_dt, InputInfo p_inputInfo)
{
	return GAME_OK;
}