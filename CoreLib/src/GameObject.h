#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SpriteInfo.h"
#include "InputInfo.h"
#include "GameStats.h"
#include <fVector2.h>
#include <TransformInfo.h>
#include <SoundInfo.h>

class GOState;
class BasicIdle;

class GameObject
{
protected:
	SpriteInfo*	m_spriteInfo;
	GameStats*	m_gameStats;

	GOState*	m_currentState;
	BasicIdle*	m_basicIdleState;
protected:
	int switchState(GOState* p_newState, bool p_forceSwitchToSame = false);
public:
	GameObject();
	GameObject(SpriteInfo* p_spriteInfo);
	GameObject(SpriteInfo* p_spriteInfo, GameStats* p_gameStats);
	virtual			~GameObject();
	virtual void	update(float p_deltaTime, InputInfo p_inputInfo);
	fVector2		getPostion() const;
	float			getRadius() const;
	SpriteInfo*		getSpriteInfo();
};

#endif
