#ifndef BOMBPILL_H
#define BOMBPILL_H

#include "Tile.h"
#include "Collectable.h"

class BombPill: public Collectable
{
private:
	Tile*			m_tile;
	SoundInfo*		m_onUseSound;
public:
	BombPill(SpriteInfo* p_spriteInfo, Tile* p_tile, GameStats* p_gameStats, CollectableContainer* p_container, SoundInfo* p_onUseSound);
	virtual ~BombPill();
	void update(float p_deltaTime, InputInfo p_inputInfo);
	void consume();
	void activate();
};

#endif