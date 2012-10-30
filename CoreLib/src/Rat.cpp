#include "Rat.h"

Rat::Rat(GameStats* p_gameStats, SpriteInfo* p_spriteInfo, Tile* p_tile, Tilemap* p_map,
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

	m_right = new Animation(fVector2(0, 0), 64, 64, 4, 0.1f, true);
	m_left = new Animation(fVector2(0, 64), 64, 64, 4, 0.1f, true);
	m_down = new Animation(fVector2(0, 128), 64, 64, 4, 0.1f, true);
	m_up = new Animation(fVector2(0, 192), 64, 64, 4, 0.1f, true);

	m_currentAnimation = m_down;
}
Rat::~Rat()
{
}