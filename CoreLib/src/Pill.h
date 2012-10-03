#ifndef PILL_H
#define PILL_H

#include "Tile.h"
#include "Collectable.h"
#include "IODevice.h"

class Pill: public Collectable
{
private:
	Tile* m_tile;
public:
	Pill(IODevice* p_io, Tile* p_tile, GameStats* p_gameStats);
	void update(float p_deltaTime, InputInfo p_inputInfo);
	void consume();
};

#endif