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
	SoundInfo* m_jumpSound;

	//Temp - To visualize jumping
	fVector2 originalSize;

	Animation* m_left;
	Animation* m_right;
	Animation* m_up;
	Animation* m_down;

	float m_airTime;

private:
	void determineAnimation();
	void checkInput(InputInfo p_inputInfo);

public:
	AvatarJumping(GameObject* p_gameObject, NavigationData* p_navigationData, GameStats* p_stats, SoundInfo* p_jumpSound);
	virtual ~AvatarJumping();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
	bool hasLanded();
};

#endif