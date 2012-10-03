#include "Avatar.h"

int Avatar::checkInput(InputInfo p_inputInfo)
{
	int desired = m_direction;
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
	//Hubba Bubba
}

Avatar::Avatar(IODevice* p_io, Tilemap* p_map, Tile* p_startTile, GameStats* p_stats)
	: GameObject(NULL, p_stats)
{
	m_direction = Direction::NONE;
	m_currentTile = m_nextTile = m_queuedTile = p_startTile;
	m_map = p_map;

	m_spriteInfo = new SpriteInfo();
	TilePosition tp = p_startTile->getTilePosition();
	float w = p_startTile->getWidth();
	float h = p_startTile->getHeight();
	m_spriteInfo->transformInfo.translation[TransformInfo::X] = tp.x * w + w * 0.5f;
	m_spriteInfo->transformInfo.translation[TransformInfo::Y] = tp.y * h + h * 0.5f;
	m_spriteInfo->transformInfo.translation[TransformInfo::Z] = 0.5f;
	m_spriteInfo->transformInfo.scale[TransformInfo::X] = w * 0.6f;
	m_spriteInfo->transformInfo.scale[TransformInfo::Y] = h * 0.6f;
	m_spriteInfo->textureFilePath = "..\\Textures\\pacman-1974_sheet.png";
	m_spriteInfo->textureRect.x		= 0;
	m_spriteInfo->textureRect.y		= 0;
	p_io->addSpriteInfo(m_spriteInfo);
	m_spriteInfo->textureRect.width = 385;
	m_spriteInfo->textureRect.height= 450;
	dt = 0;
}

void Avatar::update(float p_deltaTime, InputInfo p_inputInfo)
{
	int desired = checkInput(p_inputInfo);
	
	if (desired != m_direction)
	{
		Tile* destination = m_map->getTile(m_nextTile->getTilePosition() + Directions[desired]);
		if (destination && destination->isFree())
		{
			m_queuedTile = destination;
			m_direction = desired;
		}
	}

	dt += p_deltaTime * (3 + m_gameStats->isSpeeded() * 3);
	if (dt > 1)
	{
		dt -= 1;
		m_currentTile = m_nextTile;
		m_nextTile = m_queuedTile;

		m_queuedTile = m_map->getTile(m_nextTile->getTilePosition() + Directions[desired]);
		if (!m_queuedTile || !m_queuedTile->isFree())
			m_queuedTile = m_nextTile;

		m_currentTile->removePill();
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

