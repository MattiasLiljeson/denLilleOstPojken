#ifndef INFECTEDRAT_H
#define INFECTEDRAT_H

#include "Monster.h"

class InfectedRat: public Monster
{
private:
	bool m_rushing;
	float m_rushCooldown;

	//For respawning
	float m_timeSinceSpawn;
	static const int SPAWNTIME = 2;
	fVector2 m_size;
public:
	InfectedRat(GameStats* p_gameStats, SpriteInfo* p_spriteInfo, Tile* p_tile, Tilemap* p_map,
			SoundInfo* p_monsterKilled);
	virtual ~InfectedRat();
	void	update(float p_deltaTime, InputInfo p_inputInfo);
	void	reset();
	void	beginRespawn();
};

#endif