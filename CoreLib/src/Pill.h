#ifndef PILL_H
#define PILL_H

#include "Tile.h"
#include "Collectable.h"
#include "IODevice.h"

class PillEatenState;

class Pill: public Collectable
{
private:
	Tile* m_tile;
	PillEatenState* m_eatenState;
public:
	Pill(SpriteInfo* p_spriteInfo, SoundInfo* p_soundInfo, Tile* p_tile, GameStats* p_gameStats);
	virtual ~Pill();
	void update(float p_deltaTime, InputInfo p_inputInfo);
	virtual bool isConsumed();
	void consume();
};

#endif