#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "GameObject.h"

class Collectable: public GameObject
{
private:
public:
	Collectable();
	Collectable(SpriteInfo* p_spriteInfo);
	Collectable(SpriteInfo* p_spriteInfo, GameStats* p_gameStats);
	virtual ~Collectable();
};

#endif