#ifndef AVATARKILLED_H
#define AVATARKILLED_H

#include "GOState.h"
#include "Avatar.h"

class AvatarKilled : public GOState
{
private:
	SoundInfo* m_avatarKilledSound;
	NavigationData* m_navigationData;

	Animation* m_deathAnim;
public:
	AvatarKilled(GameObject* p_gameObject, SoundInfo* p_avatarKilledSound, NavigationData* p_navigationData);
	virtual ~AvatarKilled();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
	bool hasDied();
};

#endif