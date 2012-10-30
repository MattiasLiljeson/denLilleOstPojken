#ifndef RAT_H
#define RAT_H

#include "Monster.h"

class Rat: public Monster
{
private:
public:
	Rat(GameStats* p_gameStats, SpriteInfo* p_spriteInfo, Tile* p_tile, Tilemap* p_map,
			SoundInfo* p_monsterKilled);
	virtual ~Rat();
	void	update(float p_deltaTime, InputInfo p_inputInfo);
};

#endif