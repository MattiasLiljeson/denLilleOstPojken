#ifndef AVATARWALKING_H
#define AVATARWALKING_H

#include "GOState.h"
#include "Avatar.h"

class AvatarWalking : public GOState
{
private:
	NavigationData* m_navigationData;
	GameStats* m_gameStats;
	Animation* m_left;
	Animation* m_right;
	Animation* m_up;
	Animation* m_down;

private:
	void checkInput(InputInfo p_inputInfo);
	bool check180();
	void determineAnimation();
public:
	AvatarWalking(GameObject* p_gameObject, NavigationData* p_navigationData, GameStats* p_stats);
	virtual ~AvatarWalking();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
};

#endif