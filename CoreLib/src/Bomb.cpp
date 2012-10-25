#include "Bomb.h"

Bomb::Bomb(SpriteInfo* p_sprite, vector<pair<Tile*, SpriteInfo*> > p_flames, Tile* p_tile, Tilemap* p_map, SoundInfo* p_tick, SoundInfo* p_blast): GameObject(p_sprite)
{
	m_flameSpawn = p_flames;
	m_elapsedTime = 0.0f;
	m_currentDist = 0;
	m_start = p_tile;

	m_countDown = 0;
	m_tickSound = p_tick;
	m_tickCounter = 0;
	m_blastSound = p_blast;
}
Bomb::~Bomb()
{
	for (int i = 0; i < m_flames.size(); i++)
		delete m_flames[i];
	m_flames.clear();

	if (m_tickSound)
		m_tickSound->deleted = true;
	if (m_blastSound)
		m_blastSound->deleted = true;
}
void Bomb::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if (m_countDown > 2.2f)
	{
		if (m_currentDist > 0)
			m_spriteInfo->visible = false;
		m_elapsedTime += p_deltaTime;
	
		if (m_elapsedTime > 0.1f)
		{
			bool played = false;
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
					if (!played)
					{
						m_blastSound->play = true;
						played = true;
					}
				}
			}
			m_currentDist++;
			m_elapsedTime -= 0.1f;
		}

		for (int i = 0; i < m_flames.size(); i++)
		{
			m_flames[i]->update(p_deltaTime);
		}
	}
	else
	{
		m_tickCounter += p_deltaTime;
		if (m_tickCounter > 0.5f)
		{
			m_tickCounter -= 0.5f;
			m_tickSound->play = true;
		}
	}
	m_countDown += p_deltaTime;
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

bool Bomb::isColliding(Avatar* p_avatar)
{
	for (int i = 0; i < m_flames.size(); i++)
	{
		if (!m_flames[i]->isDead())
		{
			if (m_flames[i]->getTile() == p_avatar->getCurrentTile())
				return true;
		}
	}
	return false;
}

