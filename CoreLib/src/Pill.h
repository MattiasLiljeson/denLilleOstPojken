#ifndef PILL_H
#define PILL_H

#include "Tile.h"
#include "Collectable.h"
#include "IODevice.h"

class Pill: public Collectable
{
private:
	Tile* m_tile;
	
	//Temporary
	SoundInfo* soundInfo;
public:
	Pill(SpriteInfo* p_spriteInfo, SoundInfo* p_soundInfo, Tile* p_tile, GameStats* p_gameStats);
	void update(float p_deltaTime, InputInfo p_inputInfo);
	void consume();
};

#endif