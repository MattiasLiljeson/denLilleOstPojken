#include "AvatarKilled.h"

AvatarKilled::AvatarKilled(GameObject* p_gameObject, SoundInfo* p_avatarKilledSound, NavigationData* p_navigationData) : GOState(p_gameObject)
{
	m_avatarKilledSound = p_avatarKilledSound;
	m_navigationData = p_navigationData;
}

AvatarKilled::~AvatarKilled()
{
	if(m_avatarKilledSound)
		m_avatarKilledSound->deleted = true;
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
	m_navigationData->m_nextTile = m_navigationData->m_queuedTile = m_navigationData->m_currentTile;
	m_navigationData->m_direction = m_navigationData->m_desired = Direction::NONE;
	m_navigationData->dt = 0;
	Avatar* avatar = (Avatar*)m_gameObject;
	avatar->getSpriteInfo()->visible = true;
	return GAME_OK;
}

int AvatarKilled::update(float p_dt, InputInfo p_inputInfo)
{
	return GAME_OK;
}