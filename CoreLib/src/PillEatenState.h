#ifndef PILLEATENSTATE_H
#define PILLEATENSTATE_H

#include "GOState.h"
#include "Pill.h"

class PillEatenState : public GOState
{
private:
	SpriteInfo* m_spriteInfo;
	SoundInfo* m_onEatSound;
	GameStats* m_gameStats;
public:
	PillEatenState(GameObject* p_gameObject, SpriteInfo* p_spriteInfo, SoundInfo* p_onEatSound, GameStats* p_gameStats);
	virtual ~PillEatenState();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
};

#endif