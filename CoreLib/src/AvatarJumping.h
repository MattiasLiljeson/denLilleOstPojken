#ifndef AVATARJUMPING_H
#define AVATARJUMPING_H

#include "GOState.h"
#include "Avatar.h"

class AvatarJumping : public GOState
{
private:
	float m_elapsedTime;
	bool m_hasLanded;
	
	NavigationData* m_navigationData;

	GameStats* m_gameStats;

	//Temp - To visualize jumping
	fVector2 originalSize;
public:
	AvatarJumping(GameObject* p_gameObject, NavigationData* p_navigationData, GameStats* p_stats);
	virtual ~AvatarJumping();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
	bool hasLanded();
};

#endif