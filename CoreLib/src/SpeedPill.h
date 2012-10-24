#ifndef SPEEDPILL_H
#define SPEEDPILL_H

#include "Tile.h"
#include "Collectable.h"
#include "SpeedPillUse.h"

class SpeedPillUse;

class SpeedPill: public Collectable
{
private:
	Tile*			m_tile;
	SpeedPillUse*	m_eatenStaten;
public:
	SpeedPill(SpriteInfo* p_spriteInfo, Tile* p_tile, GameStats* p_gameStats, SoundInfo* p_onUseSound);
	virtual ~SpeedPill();
	void update(float p_deltaTime, InputInfo p_inputInfo);
	void consume();
};

#endif