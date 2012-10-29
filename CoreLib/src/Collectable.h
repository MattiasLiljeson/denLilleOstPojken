#ifndef COLLECTABLE_H
#define COLLECTABLE_H

#include "GameObject.h"

class Collectable: public GameObject
{
protected:
	bool m_consumed;
public:
	Collectable();
	Collectable(SpriteInfo* p_spriteInfo);
	Collectable(SpriteInfo* p_spriteInfo, GameStats* p_gameStats);
	virtual ~Collectable();

	virtual void consume() = 0;
	virtual bool isConsumed();
	virtual void update(float p_deltaTime, InputInfo p_inputInfo);
	virtual void activate();
};

#endif