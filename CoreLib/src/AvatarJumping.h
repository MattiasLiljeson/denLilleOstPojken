#ifndef AVATARJUMPING_H
#define AVATARJUMPING_H

#include "GOState.h"

class AvatarJumping : public GOState
{
private:
	float m_elapsedTime;
	
	//Temp - To visualize jumping
	fVector2 originalSize;
public:
	AvatarJumping(GameObject* p_gameObject);
	virtual ~AvatarJumping();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
};

#endif