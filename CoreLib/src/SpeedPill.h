#ifndef SPEEDPILL_H
#define SPEEDPILL_H

#include "Tile.h"
#include "Collectable.h"

class SpeedPill: public Collectable
{
private:
	Tile* m_tile;
	bool m_eaten;
public:
	SpeedPill(SpriteInfo* p_spriteInfo, Tile* p_tile, GameStats* p_gameStats);
	void update(float p_deltaTime, InputInfo p_inputInfo);
	void consume();
};

#endif