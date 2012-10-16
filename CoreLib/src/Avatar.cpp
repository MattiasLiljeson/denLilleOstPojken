#include "Avatar.h"
#include "AvatarKilled.h"

Avatar::Avatar(SpriteInfo* p_spriteInfo, Tilemap* p_map, Tile* p_startTile, 
	GameStats* p_stats, SoundInfo* p_avatarKilledSound)
	: GameObject(p_spriteInfo, p_stats)
{
	m_direction = m_desired = Direction::NONE;
	m_currentTile = m_nextTile = m_queuedTile = p_startTile;
	m_map = p_map;
	dt = 0;

	m_avatarKilledState = new AvatarKilled(this,p_avatarKilledSound);
}

Avatar::~Avatar()
{
	if(m_avatarKilledState)
		delete m_avatarKilledState;
}

void Avatar::checkInput(InputInfo p_inputInfo)
{
	// LEFT, RIGHT, DOWN, UP buttons.
	if (p_inputInfo.keys[InputInfo::LEFT] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::LEFT] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::LEFT;
	}
	else if (p_inputInfo.keys[InputInfo::RIGHT] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::RIGHT] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::RIGHT;
	}
	if (p_inputInfo.keys[InputInfo::DOWN] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::DOWN] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::DOWN;
	}
	else if (p_inputInfo.keys[InputInfo::UP] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::UP] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::UP;
	}
	// W, A, S, D buttons
	else if (p_inputInfo.keys[InputInfo::W_KEY] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::W_KEY] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::UP;
	}
	else if (p_inputInfo.keys[InputInfo::A_KEY] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::A_KEY] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::LEFT;
	}
	if (p_inputInfo.keys[InputInfo::S_KEY] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::S_KEY] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::DOWN;
	}
	else if (p_inputInfo.keys[InputInfo::D_KEY] == InputInfo::KEYDOWN
		|| p_inputInfo.keys[InputInfo::D_KEY] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::RIGHT;
	}
	// HACK:
	else if (p_inputInfo.keys[InputInfo::DASH] == InputInfo::KEYDOWN
		||	 p_inputInfo.keys[InputInfo::DASH] == InputInfo::KEYPRESSED)
	{
		m_desired = Direction::RIGHT;
	}
}	
bool Avatar::check180()
{
	if (m_desired == Direction::LEFT)
		if (m_direction == Direction::RIGHT)
			return true;
	if (m_desired == Direction::RIGHT)
		if (m_direction == Direction::LEFT)
			return true;
	if (m_desired == Direction::UP)
		if (m_direction == Direction::DOWN)
			return true;
	if (m_desired == Direction::DOWN)
		if (m_direction == Direction::UP)
			return true;
	return false;
}

void Avatar::update(float p_deltaTime, InputInfo p_inputInfo)
{
	checkInput(p_inputInfo);
	
	if (m_desired != m_direction)
	{
		if (check180())
		{
			Tile* destination = m_map->getTile(m_currentTile->getTilePosition() + Directions[m_desired]);
			Tile* temp = m_currentTile;
			m_currentTile = m_nextTile;
			m_nextTile = m_queuedTile = temp;
			if (destination && destination->isFree())
				m_queuedTile = destination;
			m_direction = m_desired;
			dt = 1 - dt;
		}
		else
		{
			Tile* destination = m_map->getTile(m_nextTile->getTilePosition() + Directions[m_desired]);
			if (destination && destination->isFree())
			{
				m_queuedTile = destination;
				m_direction = m_desired;
			}
		}
	}
	dt += p_deltaTime * 6;
	if (m_gameStats && m_gameStats->isSpeeded())
		dt += p_deltaTime * 3;

	if (m_currentTile)
	{
		while (dt > 1)
		{
			dt -= 1;
			m_currentTile = m_nextTile;
			m_nextTile = m_queuedTile;

			m_queuedTile = m_map->getTile(m_nextTile->getTilePosition() + Directions[m_direction]);
			if (!m_queuedTile || !m_queuedTile->isFree())
				m_queuedTile = m_nextTile;

			m_currentTile->removePill();
		}
	}
	else
		dt = 0;

	if (m_spriteInfo)
	{
		TilePosition tp1 = m_currentTile->getTilePosition();
		TilePosition tp2 = m_nextTile->getTilePosition();
		float pX = tp1.x * (1-dt) + tp2.x * dt; 
		float pY = tp1.y * (1-dt) + tp2.y * dt;  

		float w = m_currentTile->getWidth();
		float h = m_currentTile->getHeight();
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
			float w = m_currentTile->getWidth();
			float h = m_currentTile->getHeight();
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
	return m_currentTile;
}
int Avatar::getDirection()
{
	return m_direction;
}
float Avatar::getTileInterpolationFactor()
{
	return dt;
}
void Avatar::setTilePosition(Tile* p_newPosition)
{
	m_currentTile = p_newPosition;
	dt = 0;
}
void Avatar::kill()
{
	switchState(m_avatarKilledState);
}
