#ifndef SUPERPILL_H
#define SUPERPILL_H

#include "Tile.h"
#include "Collectable.h"
#include "SuperPillEaten.h"

class SuperPill : public Collectable
{
private:
	Tile* m_tile;
	SuperPillEaten* m_superPillEaten;
	float flotyAnimTick;
	TransformInfo m_origin;
public:
	SuperPill(SpriteInfo* p_spriteInfo, Tile* p_tile, GameStats* p_gameStats, SoundInfo* p_onEatSound);
	~SuperPill();
	void update(float p_deltaTime, InputInfo p_inputInfo);
	void consume();
};

#endif