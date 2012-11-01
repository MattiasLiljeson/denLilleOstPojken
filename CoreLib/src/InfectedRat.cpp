#include "InfectedRat.h"

InfectedRat::InfectedRat(GameStats* p_gameStats, SpriteInfo* p_spriteInfo, Tile* p_tile, Tilemap* p_map,
					SoundInfo* p_monsterKilledSound)
	: Monster(p_gameStats, p_spriteInfo)
{
	dt = 0;
	m_startTile = m_currentTile = m_nextTile = p_tile;
	m_map = p_map;
	m_respawning = false;
	m_dead = false;
	m_ai = NULL;

	m_monsterKilledSound = p_monsterKilledSound;

	m_right = new Animation(fVector2(0, 0), 100, 100, 4, 0.1f, true);
	m_left = new Animation(fVector2(0, 100), 100, 100, 4, 0.1f, true);
	m_down = new Animation(fVector2(0, 200), 100, 100, 4, 0.1f, true);
	m_up = new Animation(fVector2(0, 300), 100, 100, 4, 0.1f, true);

	m_currentAnimation = m_down;
	m_rushing = false;
	m_rushCooldown = 0;

	m_timeSinceSpawn = 0;
	m_size = fVector2(p_spriteInfo->transformInfo.scale[TransformInfo::X],
						p_spriteInfo->transformInfo.scale[TransformInfo::Y]);

	m_offset = fVector2(0, -25);
}
InfectedRat::~InfectedRat()
{
}
void InfectedRat::update(float p_deltaTime, InputInfo p_inputInfo)
{
	if (!m_dead)
		m_timeSinceSpawn += p_deltaTime;
	if (!m_dead && m_timeSinceSpawn > SPAWNTIME)
	{
		//Check to see if the infected rat can "see" the avatar
		if (!m_rushing && m_ai->seesTarget() && m_rushCooldown == 0 && !m_gameStats->isSuperMode())
		{
			FindPath(m_currentTile, m_ai->findRushTile());
			m_rushing = true;
			m_rushCooldown = 10;
			dt = 1 - dt;
			Tile* temp = m_currentTile;
			m_currentTile = m_nextTile;
			m_nextTile = temp;
		}


		m_rushCooldown = max(0.0f, m_rushCooldown - p_deltaTime);
		dt += p_deltaTime * (6 + m_rushing * 6);
		while (dt > 1)
		{
			dt -= 1;
			if (m_currentTile)
			{
				m_currentTile = m_nextTile;
				if (m_path.size() > 0)
				{
					if (m_path.back()->isFree())
					{
						m_nextTile = m_path.back();
						m_path.pop_back();
					}
					else
					{
						m_path.clear();
					}
				}
				else
				{
					if(m_path.size() == 0)
					{
						Tile* t;
						do
						{
							int rndX = rand() % m_map->getWidth();
							int rndY = rand() % m_map->getHeight();
							t = m_map->getTile(TilePosition(rndX, rndY));					
						} while (!t->isFree());

						FindPath(m_currentTile, t);
						m_rushing = false;
					}
				}
			}
		}
	}
	if(m_spriteInfo)
	{
		determineAnimation();
		transformSpriteInformation();

		if (m_currentAnimation)
		{
			if (m_currentTile != m_nextTile)
				m_currentAnimation->update(p_deltaTime);
			m_spriteInfo->textureRect = m_currentAnimation->getCurrentFrame();
		}

		if (m_timeSinceSpawn < SPAWNTIME)
		{
			float frac = m_timeSinceSpawn / SPAWNTIME;
			m_spriteInfo->transformInfo.scale[TransformInfo::X] = m_size.x * frac;
			m_spriteInfo->transformInfo.scale[TransformInfo::Y] = m_size.y * frac;
		}

		if (m_currentAnimation == m_right)
			m_offset = fVector2(15, 10);
		else if (m_currentAnimation == m_left)
			m_offset = fVector2(-15, 10);
		else if (m_currentAnimation == m_up)
			m_offset = fVector2(0, 15);
		else if (m_currentAnimation == m_down)
			m_offset = fVector2(0, -15);
		m_spriteInfo->transformInfo.translation[TransformInfo::X] += m_offset.x;
		m_spriteInfo->transformInfo.translation[TransformInfo::Y] += m_offset.y;
	}
}
void InfectedRat::reset()
{
	Monster::reset();
	m_timeSinceSpawn = 0;
	m_spriteInfo->transformInfo.scale[TransformInfo::X] = 0;
	m_spriteInfo->transformInfo.scale[TransformInfo::Y] = 0;
}
void InfectedRat::beginRespawn()
{
	Monster::beginRespawn();
	m_timeSinceSpawn = 0;
	m_spriteInfo->transformInfo.scale[TransformInfo::X] = 0;
	m_spriteInfo->transformInfo.scale[TransformInfo::Y] = 0;
}