#ifndef SPEEDPILLUSE_H
#define SPEEDPILLUSE_H

#include "GOState.h"
#include "SpeedPill.h"

class SpeedPillUse : public GOState
{
private:
	SoundInfo* m_onUseSound;
public:
	SpeedPillUse(GameObject* p_gameObject, SoundInfo* p_onUseSound);
	virtual ~SpeedPillUse();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
};

#endif