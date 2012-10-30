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

	m_airTime = 0.5f;
	int frames = 8;
	float frac = m_airTime / frames;
	m_right = new Animation(fVector2(0, 256), 64, 64, frames, frac, true);
	m_left = new Animation(fVector2(0, 320), 64, 64, frames, frac, true);
	m_down = new Animation(fVector2(0, 384), 64, 64, frames, frac, true);
	m_up = new Animation(fVector2(0, 448), 64, 64, frames, frac, true);
}

void AvatarJumping::checkInput(InputInfo p_inputInfo)
{
	int m_desired = m_navigationData->m_desired;
	if (p_inputInfo.keys[InputInfo::LEFT] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::LEFT] == InputInfo::KEYPRESSED
		|| p_inputInfo.keys[InputInfo::A_KEY] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::A_KEY] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::LEFT;
	}
	else if (p_inputInfo.keys[InputInfo::RIGHT] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::RIGHT] == InputInfo::KEYPRESSED
		|| p_inputInfo.keys[InputInfo::D_KEY] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::D_KEY] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::RIGHT;
	}
	if (p_inputInfo.keys[InputInfo::DOWN] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::DOWN] == InputInfo::KEYPRESSED
		|| p_inputInfo.keys[InputInfo::S_KEY] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::S_KEY] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::DOWN;
	}
	else if (p_inputInfo.keys[InputInfo::UP] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::UP] == InputInfo::KEYPRESSED
		|| p_inputInfo.keys[InputInfo::W_KEY] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::W_KEY] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::UP;
	}
	m_navigationData->m_desired = m_desired;
}	

AvatarJumping::~AvatarJumping()
{
	if (m_jumpSound)
		m_jumpSound->deleted = true;

	delete m_right;
	delete m_left; 
	delete m_down; 
	delete m_up;
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

	checkInput(p_inputInfo);

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
	float jumptime = this->m_airTime;

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