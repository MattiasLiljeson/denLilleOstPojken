#include "Avatar.h"

Direction Avatar::checkInput(InputInfo p_inputInfo)
{
	Direction desired = m_direction;
	if (p_inputInfo.keys[InputInfo::LEFT] == InputInfo::KEYDOWN)
	{
		desired = Direction::LEFT;
	}
	else if (p_inputInfo.keys[InputInfo::RIGHT] == InputInfo::KEYDOWN)
	{
		desired = Direction::RIGHT;
	}
	if (p_inputInfo.keys[InputInfo::DOWN] == InputInfo::KEYDOWN)
	{
		desired = Direction::DOWN;
	}
	else if (p_inputInfo.keys[InputInfo::UP] == InputInfo::KEYDOWN)
	{
		desired = Direction::UP;
	}
	return desired;
}

Avatar::Avatar()
{

}

Avatar::Avatar( SpriteInfo* p_spriteInfo, Tilemap* p_map, Tile* p_startTile)
	: GameObject(p_spriteInfo)
{
	m_direction = Direction::NONE;
	m_currentTile = m_nextTile = m_queuedTile = p_startTile;
	m_map = p_map;
	if (p_spriteInfo)
	{
		TilePosition tp = p_startTile->getTilePosition();
		float w = p_startTile->getWidth();
		float h = p_startTile->getHeight();
		p_spriteInfo->transformInfo.translation[TransformInfo::X] = tp.x * w + w * 0.5f;
		p_spriteInfo->transformInfo.translation[TransformInfo::Y] = tp.y * h + h * 0.5f;
		p_spriteInfo->transformInfo.scale[TransformInfo::X] = w * 0.6f;
		p_spriteInfo->transformInfo.scale[TransformInfo::Y] = h * 0.6f;
	}
	dt = 0;
}

void Avatar::update(float p_deltaTime, InputInfo p_inputInfo)
{
	Direction desired = checkInput(p_inputInfo);
	
	if (desired != m_direction)
	{
		Tile* destination = m_map->getTile(m_nextTile->getTilePosition() + Directions[desired]);
		if (destination && destination->isFree())
		{
			m_queuedTile = destination;
			m_direction = desired;
		}
	}

	dt += p_deltaTime * 3;
	if (dt > 1)
	{
		dt -= 1;
		m_currentTile = m_nextTile;
		m_nextTile = m_queuedTile;

		m_queuedTile = m_map->getTile(m_nextTile->getTilePosition() + Directions[desired]);
		if (!m_queuedTile || !m_queuedTile->isFree())
			m_queuedTile = m_nextTile;
	}

	TilePosition tp1 = m_currentTile->getTilePosition();
	TilePosition tp2 = m_nextTile->getTilePosition();
	float pX = tp1.x * (1-dt) + tp2.x * dt; 
	float pY = tp1.y * (1-dt) + tp2.y * dt;  

	float w = m_currentTile->getWidth();
	float h = m_currentTile->getHeight();
	m_spriteInfo->transformInfo.translation[TransformInfo::X] = pX * w + w * 0.5f;
	m_spriteInfo->transformInfo.translation[TransformInfo::Y] = pY * h + h * 0.5f;

}

