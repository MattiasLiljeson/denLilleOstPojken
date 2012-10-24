#include "AvatarKilled.h"

AvatarKilled::AvatarKilled(GameObject* p_gameObject, SoundInfo* p_avatarKilledSound, NavigationData* p_navigationData) : GOState(p_gameObject)
{
	m_avatarKilledSound = p_avatarKilledSound;
	m_navigationData = p_navigationData;
	m_deathAnim = new Animation(fVector2(0, 512), 64, 64, 8, 0.25f);
}

AvatarKilled::~AvatarKilled()
{
	if(m_avatarKilledSound)
		m_avatarKilledSound->deleted = true;
	delete m_deathAnim;
}

int AvatarKilled::onEnter()
{
	Avatar* avatar = (Avatar*)m_gameObject;
	m_avatarKilledSound->play = true;
	m_deathAnim->restart();

	return GAME_OK;
}

int AvatarKilled::onExit()
{
	m_navigationData->m_nextTile = m_navigationData->m_queuedTile = m_navigationData->m_currentTile;
	m_navigationData->m_direction = m_navigationData->m_desired = Direction::NONE;
	m_navigationData->dt = 0;
	Avatar* avatar = (Avatar*)m_gameObject;
	return GAME_OK;
}

int AvatarKilled::update(float p_dt, InputInfo p_inputInfo)
{
	Avatar* av = (Avatar*)m_gameObject;
	av->setCurrentAnimation(m_deathAnim);
	m_deathAnim->update(p_dt);
	return GAME_OK;
}
bool AvatarKilled::hasDied()
{
	return m_deathAnim->hasFinished();
}