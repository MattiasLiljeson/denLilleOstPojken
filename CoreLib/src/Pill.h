#ifndef PILL_H
#define PILL_H

#include "Tile.h"

class Pill: public GameObject
{
private:
	Tile* m_tile;
public:
	Pill(SpriteInfo* p_spriteInfo, Tile* p_tile);
};

#endif