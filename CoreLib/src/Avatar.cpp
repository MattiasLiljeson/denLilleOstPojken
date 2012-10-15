#include "Avatar.h"
#include "AvatarKilled.h"
#include "AvatarJumping.h"
#include "AvatarWalking.h"

Avatar::Avatar(SpriteInfo* p_spriteInfo, Tilemap* p_map, Tile* p_startTile, 
	GameStats* p_stats, SoundInfo* p_avatarKilledSound)
	: GameObject(p_spriteInfo, p_stats)
{
	m_navigationData = new NavigationData();
	m_navigationData->m_direction = m_navigationData->m_desired = Direction::NONE;
	m_navigationData->m_currentTile = m_navigationData->m_nextTile = m_navigationData->m_queuedTile = p_startTile;
	m_navigationData->dt = 0;
	m_navigationData->m_map = p_map;

	m_avatarKilledState = new AvatarKilled(this,p_avatarKilledSound);
	m_avatarJumpingState = new AvatarJumping(this, m_navigationData, p_stats);
	m_walking = new AvatarWalking(this, m_navigationData, p_stats);
	switchState(m_walking);
}

Avatar::~Avatar()
{
	if(m_avatarKilledState)
		delete m_avatarKilledState;
	if (m_avatarJumpingState)
		delete m_avatarJumpingState;
}
void Avatar::update(float p_deltaTime, InputInfo p_inputInfo)
{
	GameObject::update(p_deltaTime, p_inputInfo);

	if (p_inputInfo.keys[InputInfo::SPACE] == InputInfo::KEYPRESSED)
	{
		switchState(m_avatarJumpingState);
	}
	if (m_currentState == m_avatarJumpingState && m_avatarJumpingState->hasLanded())
	{
 		switchState(m_walking);
	}

	if (m_spriteInfo)
	{
		TilePosition tp1 = m_navigationData->m_currentTile->getTilePosition();
		TilePosition tp2 = m_navigationData->m_nextTile->getTilePosition();
		float pX = tp1.x * (1-m_navigationData->dt) + tp2.x * m_navigationData->dt; 
		float pY = tp1.y * (1-m_navigationData->dt) + tp2.y * m_navigationData->dt;  

		float w = m_navigationData->m_currentTile->getWidth();
		float h = m_navigationData->m_currentTile->getHeight();
		m_spriteInfo->transformInfo.translation[TransformInfo::X] = pX * w + w * 0.5f;
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] = pY * h + h * 0.5f;
	
		if (m_gameStats && m_gameStats->isSuperMode())
		{
			m_spriteInfo->textureRect.x = 0;
			float remaining = m_gameStats->superTimeRemaining();
			if (remaining < 1)
			{
				if ((int)(remaining*6) % 2 == 0)
					m_spriteInfo->textureRect.x = m_spriteInfo->textureRect.width;
			}
		}
		else
		{
			float w = m_navigationData->m_currentTile->getWidth();
			float h = m_navigationData->m_currentTile->getHeight();
			m_spriteInfo->transformInfo.translation[TransformInfo::X] = pX * w + w * 0.5f;
			m_spriteInfo->transformInfo.translation[TransformInfo::Y] = pY * h + h * 0.5f;
		}
		if (m_gameStats->isSuperMode())
		{
			m_spriteInfo->textureRect.x = 0;
			float remaining = m_gameStats->superTimeRemaining();
			if (remaining < 1)
			{
				if ((int)(remaining*6) % 2 == 0)
					m_spriteInfo->textureRect.x = m_spriteInfo->textureRect.width;
			}
		}
		else
		{
			m_spriteInfo->textureRect.x = m_spriteInfo->textureRect.width;
		}
	}
}
Tile* Avatar::getCurrentTile()
{
	return m_navigationData->m_currentTile;
}
int Avatar::getDirection()
{
	return m_navigationData->m_direction;
}
float Avatar::getTileInterpolationFactor()
{
	return m_navigationData->dt;
}
void Avatar::setTilePosition(Tile* p_newPosition)
{
	m_navigationData->m_currentTile = p_newPosition;
	m_navigationData->dt = 0;
}
void Avatar::kill()
{
	switchState(m_avatarKilledState);
}
bool Avatar::inAir()
{
	return m_currentState == m_avatarJumpingState;
}
