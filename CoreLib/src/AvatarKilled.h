#ifndef AVATARKILLED_H
#define AVATARKILLED_H

#include "GOState.h"
#include "Avatar.h"

class AvatarKilled : public GOState
{
private:
	SoundInfo* m_avatarKilledSound;
public:
	AvatarKilled(GameObject* p_gameObject, SoundInfo* p_avatarKilledSound);
	virtual ~AvatarKilled();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
};

#endif