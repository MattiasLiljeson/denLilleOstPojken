#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SpriteInfo.h"
#include "InputInfo.h"

class GameObject
{
protected:
	SpriteInfo*	m_spriteInfo;

public:
	GameObject();
	GameObject(SpriteInfo* p_spriteInfo);
	virtual ~GameObject();

	virtual void update(float p_deltaTime, InputInfo p_inputInfo);
};

#endif