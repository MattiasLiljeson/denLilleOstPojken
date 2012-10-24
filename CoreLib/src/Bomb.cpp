#include "Bomb.h"

Bomb::Bomb(vector<pair<Tile*, SpriteInfo*> > p_flames, Tile* p_tile, Tilemap* p_map): GameObject(NULL)
{
	m_flameSpawn = p_flames;
	m_elapsedTime = 0.0f;
	m_currentDist = 1;
	m_start = p_tile;

	for (int i = 0; i < m_flameSpawn.size(); i++)
	{
		m_flameSpawn[i].second->visible = false;
		TilePosition diff = m_flameSpawn[i].first->getTilePosition() - m_start->getTilePosition();
		int l = abs(diff.x) + abs(diff.y);
		if (l-m_currentDist <= 0 && l-m_currentDist > -2)
		{
			m_flames.push_back(new Flame(m_flameSpawn[i].second, m_flameSpawn[i].first));
			m_flameSpawn[i].second->visible = true;
			m_flameSpawn[i] = m_flameSpawn.back();
			m_flameSpawn.pop_back();
			i--;
		}
	}
}
Bomb::~Bomb()
{
	for (int i = 0; i < m_flames.size(); i++)
		delete m_flames[i];
	m_flames.clear();
}
void Bomb::update(float p_deltaTime, InputInfo p_inputInfo)
{
	m_elapsedTime += p_deltaTime;
	
	if (m_elapsedTime > 0.1f)
	{
		m_currentDist++;
		for (int i = 0; i < m_flameSpawn.size(); i++)
		{
			TilePosition diff = m_flameSpawn[i].first->getTilePosition() - m_start->getTilePosition();
			int l = abs(diff.x) + abs(diff.y);
			if (l-m_currentDist <= 0 && l-m_currentDist > -2)
			{
				m_flames.push_back(new Flame(m_flameSpawn[i].second, m_flameSpawn[i].first));
				m_flameSpawn[i].second->visible = true;
				m_flameSpawn[i] = m_flameSpawn.back();
				m_flameSpawn.pop_back();
				i--;
			}
		}
		m_elapsedTime -= 0.1f;
	}

	for (int i = 0; i < m_flames.size(); i++)
	{
		m_flames[i]->update(p_deltaTime);
	}
}
bool Bomb::isColliding(Monster* p_monster)
{
	for (int i = 0; i < m_flames.size(); i++)
	{
		if (!m_flames[i]->isDead())
		{
			if (m_flames[i]->getTile() == p_monster->getCurrentTile())
				return true;
		}
	}
	return false;
}
