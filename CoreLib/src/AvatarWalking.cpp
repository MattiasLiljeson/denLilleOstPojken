#include "AvatarWalking.h"

AvatarWalking::AvatarWalking(GameObject* p_gameObject, NavigationData* p_navigationData, GameStats* p_stats) : GOState(p_gameObject)
{
	m_navigationData = p_navigationData;
	m_gameStats = p_stats;
}

AvatarWalking::~AvatarWalking()
{
}

int AvatarWalking::onEnter()
{
	return GAME_OK;
}

int AvatarWalking::onExit()
{
	return GAME_OK;
}

void AvatarWalking::checkInput(InputInfo p_inputInfo)
{
	int m_desired = m_navigationData->m_desired;
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
	m_navigationData->m_desired = m_desired;
}	
bool AvatarWalking::check180()
{
	Avatar* av = ((Avatar*)m_gameObject);
	int dir = av->getDirection();
	int m_desired = m_navigationData->m_desired;
	if (m_desired == Direction::LEFT)
		if (dir == Direction::RIGHT)
			return true;
	if (m_desired == Direction::RIGHT)
		if (dir == Direction::LEFT)
			return true;
	if (m_desired == Direction::UP)
		if (dir == Direction::DOWN)
			return true;
	if (m_desired == Direction::DOWN)
		if (dir == Direction::UP)
			return true;
	return false;
}

int AvatarWalking::update(float p_dt, InputInfo p_inputInfo)
{
	Avatar* av = ((Avatar*)m_gameObject);

	checkInput(p_inputInfo);
	
	if (m_navigationData->m_desired != m_navigationData->m_direction)
	{
		if (check180())
		{
			Tile* destination = m_navigationData->m_map->getTile(m_navigationData->m_currentTile->getTilePosition() + Directions[m_navigationData->m_desired]);
			Tile* temp = m_navigationData->m_currentTile;
			m_navigationData->m_currentTile = m_navigationData->m_nextTile;
			m_navigationData->m_nextTile = m_navigationData->m_queuedTile = temp;
			if (destination && destination->isFree())
				m_navigationData->m_queuedTile = destination;
			m_navigationData->m_direction = m_navigationData->m_desired;
			m_navigationData->dt = 1 - m_navigationData->dt;
		}
		else
		{
			Tile* destination = m_navigationData->m_map->getTile(m_navigationData->m_nextTile->getTilePosition() + Directions[m_navigationData->m_desired]);
			if (destination && destination->isFree())
			{
				m_navigationData->m_queuedTile = destination;
				m_navigationData->m_direction = m_navigationData->m_desired;
			}
		}
	}
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

	return GAME_OK;
}