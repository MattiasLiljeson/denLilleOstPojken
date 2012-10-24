#ifndef TRAP_H
#define TRAP_H

#include "Tilemap.h"

class Trap: public GameObject
{
private:
public:
	Trap(SpriteInfo* p_spriteInfo, Tile* p_tile, Tilemap* p_map);
	virtual ~Trap();
	void	update(float p_deltaTime, InputInfo p_inputInfo);
};

#endif