#ifndef RAT_H
#define RAT_H

#include "Monster.h"

class Rat: public Monster
{
private:

	//For respawning
	float m_timeSinceSpawn;
	static const int SPAWNTIME = 2;
	fVector2 m_size;
public:
	Rat(GameStats* p_gameStats, SpriteInfo* p_spriteInfo, Tile* p_tile, Tilemap* p_map,
			SoundInfo* p_monsterKilled);
	virtual ~Rat();
	void	update(float p_deltaTime, InputInfo p_inputInfo);
	void	reset();
	void	beginRespawn();
};

#endif