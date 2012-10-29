#include "Avatar.h"
#include "AvatarKilled.h"
#include "AvatarJumping.h"
#include "AvatarWalking.h"

Avatar::Avatar(SpriteInfo* p_spriteInfo, SpriteInfo* p_shadow, Tilemap* p_map, Tile* p_startTile, 
	GameStats* p_stats, SoundInfo* p_avatarKilledSound, SoundInfo* p_jumpSound)
	: GameObject(p_spriteInfo, p_stats)
{
	m_navigationData = new NavigationData();
	m_navigationData->m_direction = Direction::NONE;
	m_navigationData->m_desired = Direction::NONE;
	m_navigationData->m_currentTile = p_startTile;
	m_navigationData->m_nextTile = p_startTile;
	m_navigationData->m_queuedTile = p_startTile;
	m_navigationData->dt = 0;
	m_navigationData->m_map = p_map;

	m_avatarKilledState = new AvatarKilled(this,p_avatarKilledSound, m_navigationData);
	m_avatarJumpingState = new AvatarJumping(this, m_navigationData, p_stats, p_jumpSound);
	m_walking = new AvatarWalking(this, m_navigationData, p_stats);
	switchState(m_walking);

	m_currentAnimation = NULL;
	if (m_spriteInfo)
		m_size = fVector2(p_spriteInfo->transformInfo.scale[TransformInfo::X], p_spriteInfo->transformInfo.scale[TransformInfo::Y]);
	else
		m_size = fVector2();

	if (m_spriteInfo)
		m_offset = 16 * m_spriteInfo->transformInfo.scale[TransformInfo::Y] / 64;
	else
		m_offset = 0;

	m_shadow = p_shadow;
	if (m_shadow)
		m_shadow->visible = false;
}

Avatar::~Avatar()
{
	if(m_avatarKilledState)
		delete m_avatarKilledState;
	if (m_avatarJumpingState)
		delete m_avatarJumpingState;
	if (m_walking)
		delete m_walking;
	if (m_navigationData)
		delete m_navigationData;
}

void Avatar::update(float p_deltaTime, InputInfo p_inputInfo)
{
	GameObject::update(p_deltaTime, p_inputInfo);

	if (p_inputInfo.keys[InputInfo::SPACE] == InputInfo::KEYPRESSED)
	{
		if (m_currentState != m_avatarKilledState)
			switchState(m_avatarJumpingState);
	}
	if (m_currentState == m_avatarJumpingState && m_avatarJumpingState->hasLanded())
	{
		switchState(m_walking);
	}

	if (m_currentAnimation)
	{
		m_currentAnimation->update(p_deltaTime);
		
		if (m_spriteInfo)
			m_spriteInfo->textureRect = m_currentAnimation->getCurrentFrame();
	}

	if (m_spriteInfo)
	{
		TilePosition tp1 = m_navigationData->m_currentTile->getTilePosition();
		TilePosition tp2 = m_navigationData->m_nextTile->getTilePosition();
		float pX = tp1.x * (1-m_navigationData->dt) + tp2.x * m_navigationData->dt; 
		float pY = tp1.y * (1-m_navigationData->dt) + tp2.y * m_navigationData->dt;  

		float w = m_navigationData->m_currentTile->getWidth();
		float h = m_navigationData->m_currentTile->getHeight();
		m_spriteInfo->transformInfo.translation[TransformInfo::X] =
			pX * w + w * 0.5f;
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] =
			pY * h + h * 0.5f /*temp*/ + m_offset;
	

		bool super = false;
		if (m_gameStats->isSuperMode())
		{
			float remaining = m_gameStats->superTimeRemaining();
			if ((int)(remaining*6) % 2 != 0 || remaining >= 1)
			{
				super = true;
				if (remaining > 5)
				{
					m_spriteInfo->transformInfo.scale[TransformInfo::X] = m_size.x*(1 + 6-remaining);
					m_spriteInfo->transformInfo.scale[TransformInfo::Y] = m_size.y*(1 + 6 - remaining);
					m_offset = (16 + 8 * (6-remaining)) * m_spriteInfo->transformInfo.scale[TransformInfo::Y] / 64;
				}
				else
				{
					m_spriteInfo->transformInfo.scale[TransformInfo::X] = m_size.x*2;
					m_spriteInfo->transformInfo.scale[TransformInfo::Y] = m_size.y*2;
					m_offset = 24 * m_spriteInfo->transformInfo.scale[TransformInfo::Y] / 64;
				}
			}
		}
		if (!super)
		{
			m_spriteInfo->transformInfo.scale[TransformInfo::X] = m_size.x;
			m_spriteInfo->transformInfo.scale[TransformInfo::Y] = m_size.y;
			m_offset = 16 * m_spriteInfo->transformInfo.scale[TransformInfo::Y] / 64;
		}

		if (m_shadow)
		{
			if (m_gameStats->isSpeeded())
			{
				if (m_shadowQueue.size() == 0)
				{
					m_shadowQueue.push_back(m_navigationData->m_currentTile);
					m_shadowQueue.push_back(m_navigationData->m_nextTile);
					m_shadowDT = m_navigationData->dt;
				}
				if (m_shadowQueue.back() != m_navigationData->m_nextTile)
				{
					m_shadowQueue.push_back(m_navigationData->m_nextTile);
				}

				float frac = m_gameStats->speededPercentElapsed();

				if (m_navigationData->m_currentTile != m_navigationData->m_nextTile)
					m_shadowDT += p_deltaTime * (6 + 6*frac);
				else
					m_shadowDT += p_deltaTime * 6 * frac;
				while (m_shadowDT > 1 && m_shadowQueue.size() > 0)
				{
					m_shadowDT -= 1;
					m_shadowQueue.pop_front();
				}

				fVector2 pos;
				if (m_shadowQueue.size() > 1)
				{
					pos = m_shadowQueue[0]->getPosition() * (1-m_shadowDT) + m_shadowQueue[1]->getPosition() * m_shadowDT;
					pos.y += m_offset;
					if (m_shadowQueue[1] == m_navigationData->m_nextTile && m_shadowDT > m_navigationData->dt)
						pos = fVector2(m_spriteInfo->transformInfo.translation[TransformInfo::X], m_spriteInfo->transformInfo.translation[TransformInfo::Y]);
				}
				else
					pos = fVector2(m_spriteInfo->transformInfo.translation[TransformInfo::X], m_spriteInfo->transformInfo.translation[TransformInfo::Y]);

				m_shadow->visible = true;
				m_shadow->textureRect = m_spriteInfo->textureRect;
				m_shadow->transformInfo = m_spriteInfo->transformInfo;
				m_shadow->transformInfo.translation[TransformInfo::X] = pos.x;
				m_shadow->transformInfo.translation[TransformInfo::Y] = pos.y;
			}
			else
			{
				m_shadowQueue.clear();
				m_shadow->visible = false;
			}
		}
	}
}
Tile* Avatar::getCurrentTile()
{
	return m_navigationData->m_currentTile;
}
Tile* Avatar::getClosestTile()
{
	if (m_navigationData->dt > 0.5f)
		return m_navigationData->m_nextTile;
	else
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
	if (m_currentState != m_avatarKilledState)
	{
		switchState(m_avatarKilledState);
		m_gameStats->clearBuffs();
	}
}
bool Avatar::inAir()
{
	return m_currentState == m_avatarJumpingState;
}
bool Avatar::isDead()
{
	return m_currentState == m_avatarKilledState && m_avatarKilledState->hasDied();
}
void Avatar::revive(Tile* p_newPosition)
{
	m_navigationData->m_currentTile = p_newPosition;
	switchState(m_walking);
}
void Avatar::setCurrentAnimation(Animation* p_animation)
{
	m_currentAnimation = p_animation;
}
fVector2 Avatar::getPostion()
{
	float dt = m_navigationData->dt;
	fVector2 p1 = m_navigationData->m_currentTile->getPosition();
	fVector2 p2 = m_navigationData->m_nextTile->getPosition();
	return p1 * (1-dt) + p2 * dt;
}
void Avatar::reset()
{

}
