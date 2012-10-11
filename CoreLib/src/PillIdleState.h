#ifndef PILLIDLESTATE_H
#define PILLIDLESTATE_H

#include "GOState.h"
#include "PillIdleState.h"
#include <InputInfo.h>

class PillIdleState: public GOState
{
private:
	SpriteInfo* m_spriteInfo;
public:
	PillIdleState(GameObject* p_gameObject, SpriteInfo* p_spriteInfo);
	virtual ~PillIdleState();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
};

#endif