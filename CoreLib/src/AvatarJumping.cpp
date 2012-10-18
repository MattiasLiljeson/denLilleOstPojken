#include "AvatarJumping.h"

AvatarJumping::AvatarJumping(GameObject* p_gameObject, NavigationData* p_navigationData, GameStats* p_stats, SoundInfo* p_jumpSound) : GOState(p_gameObject)
{
	m_elapsedTime = 0;
	m_navigationData = p_navigationData;
	if (p_gameObject && p_gameObject->getSpriteInfo())
	{
		originalSize.x = p_gameObject->getSpriteInfo()->transformInfo.scale[TransformInfo::X];
		originalSize.y = p_gameObject->getSpriteInfo()->transformInfo.scale[TransformInfo::Y];
	}
	m_gameStats = p_stats;
	m_jumpSound = p_jumpSound;

	m_right = new Animation(fVector2(0, 256), 64, 64, 8, 0.08f, true);
	m_left = new Animation(fVector2(0, 320), 64, 64, 8, 0.08f, true);
	m_down = new Animation(fVector2(0, 384), 64, 64, 8, 0.08f, true);
	m_up = new Animation(fVector2(0, 448), 64, 64, 8, 0.08f, true);
}

AvatarJumping::~AvatarJumping()
{
	if (m_jumpSound)
		m_jumpSound->deleted = true;
}

int AvatarJumping::onEnter()
{
	m_hasLanded = false;
	m_elapsedTime = 0;
	m_jumpSound->play = true;
	return GAME_OK;
}

int AvatarJumping::onExit()
{
	return GAME_OK;
}

int AvatarJumping::update(float p_dt, InputInfo p_inputInfo)
{
	Avatar* av = ((Avatar*)m_gameObject);
	//Move logic
	m_navigationData->dt += p_dt * 6;
	if (m_gameStats && m_gameStats->isSpeeded())
		m_navigationData->dt += p_dt * 3;

	if (m_navigationData->m_currentTile)
	{
		while (m_navigationData->dt > 1)
		{
			m_navigationData->dt -= 1;
			m_navigationData->m_currentTile = m_navigationData->m_nextTile;
			m_navigationData->m_nextTile = m_navigationData->m_queuedTile;

			m_navigationData->m_queuedTile = m_navigationData->m_map->getTile(m_navigationData->m_nextTile->getTilePosition() + Directions[av->getDirection()]);
			if (!m_navigationData->m_queuedTile || !m_navigationData->m_queuedTile->isFree())
				m_navigationData->m_queuedTile = m_navigationData->m_nextTile;

			m_navigationData->m_currentTile->removePill();
		}
	}
	else
		m_navigationData->dt = 0;
	
	//Jump logic
	float jumptime = 0.08f * 8;
	float factor;
	if (m_elapsedTime <= jumptime * 0.5f)
		factor = m_elapsedTime / (jumptime*0.5f);
	else
		factor = (jumptime - m_elapsedTime) / (jumptime*0.5f);
	if (m_gameObject && m_gameObject->getSpriteInfo())
	{
		factor *= 0.25f;
		m_gameObject->getSpriteInfo()->transformInfo.scale[TransformInfo::X] = originalSize.x * (1+factor);
		m_gameObject->getSpriteInfo()->transformInfo.scale[TransformInfo::Y] = originalSize.y * (1+factor);
	}
	m_elapsedTime += p_dt;
	if (m_elapsedTime > jumptime)
		m_hasLanded = true;

	determineAnimation();

	return GAME_OK;
}
bool AvatarJumping::hasLanded()
{
	return m_hasLanded;
}
void AvatarJumping::determineAnimation()
{
	Avatar* av = (Avatar*)m_gameObject;
	if (m_navigationData->m_direction == Direction::LEFT)
	{
		av->setCurrentAnimation(m_left);
	}
	else if (m_navigationData->m_direction == Direction::RIGHT)
	{
		av->setCurrentAnimation(m_right);
	}
	else if (m_navigationData->m_direction == Direction::UP)
	{
		av->setCurrentAnimation(m_up);
	}
	else if (m_navigationData->m_direction == Direction::DOWN)
	{
		av->setCurrentAnimation(m_down);
	}
}