#ifndef PILL_H
#define PILL_H

#include "Tile.h"
#include "Collectable.h"

class Pill: public Collectable
{
private:
	Tile* m_tile;
	bool m_eaten;
public:
	Pill(SpriteInfo* p_spriteInfo, Tile* p_tile, GameStats* p_gameStats);
	void update(float p_deltaTime, InputInfo p_inputInfo);
	void consume();
};

#endif