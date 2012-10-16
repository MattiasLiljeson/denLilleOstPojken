#include "Bomb.h"

Bomb::Bomb(vector<pair<Tile*, SpriteInfo*>> p_flames, Tile* p_tile, Tilemap* p_map): GameObject(NULL)
{
	m_flames = p_flames;
	m_elapsedTime = 0.0f;
	m_currentDist = 1;
	m_start = p_tile;
	for (int i = 0; i < m_flames.size(); i++)
	{
		TilePosition diff = m_flames[i].first->getTilePosition() - m_start->getTilePosition();
		int l = abs(diff.x) + abs(diff.y);
		if (l-m_currentDist <= 0 && l-m_currentDist > -2)
			m_flames[i].second->visible = true;
		else
			m_flames[i].second->visible = false;
	}
}
Bomb::~Bomb()
{
}
void Bomb::update(float p_deltaTime, InputInfo p_inputInfo)
{
	m_elapsedTime += p_deltaTime;
	
	if (m_elapsedTime > 0.2f)
	{
		m_currentDist++;
		for (int i = 0; i < m_flames.size(); i++)
		{
			TilePosition diff = m_flames[i].first->getTilePosition() - m_start->getTilePosition();
			int l = abs(diff.x) + abs(diff.y);
			if (l-m_currentDist <= 0 && l-m_currentDist > -2)
				m_flames[i].second->visible = true;
			else
				m_flames[i].second->visible = false;
		}
		m_elapsedTime -= 0.2f;
	}
}
bool Bomb::isColliding(Monster* p_monster)
{
	for (int i = 0; i < m_flames.size(); i++)
	{
		if (m_flames[i].second->visible)
		{
			if (m_flames[i].first == p_monster->getCurrentTile())
				return true;
		}
	}
	return false;
}