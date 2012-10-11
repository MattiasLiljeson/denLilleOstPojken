#ifndef PILLEATENSTATE_H
#define PILLEATENSTATE_H

#include "GOState.h"
#include "Pill.h"

class PillEatenState : public GOState
{
private:
	SpriteInfo* m_spriteInfo;
public:
	PillEatenState(GameObject* p_gameObject, SpriteInfo* p_spriteInfo);
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
};

#endif