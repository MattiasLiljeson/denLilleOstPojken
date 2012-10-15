#include "AvatarKilled.h"

AvatarKilled::AvatarKilled(GameObject* p_gameObject, SoundInfo* p_avatarKilledSound) : GOState(p_gameObject)
{
	m_avatarKilledSound = p_avatarKilledSound;
}

AvatarKilled::~AvatarKilled()
{

}

int AvatarKilled::onEnter()
{
	Avatar* avatar = (Avatar*)m_gameObject;
	m_avatarKilledSound->play = true;
	avatar->getSpriteInfo()->visible = false;
	return GAME_OK;
}

int AvatarKilled::onExit()
{
	return GAME_OK;
}

int AvatarKilled::update(float p_dt, InputInfo p_inputInfo)
{
	return GAME_OK;
}