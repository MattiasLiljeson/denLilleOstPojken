#ifndef SUPERPILLEATEN_H
#define SUPERPILLEATEN_H

#include "GOState.h"

class SuperPillEaten : public GOState
{
private:
	SoundInfo* m_onEatSound;
public:
	SuperPillEaten(GameObject* p_gameObject, SoundInfo* p_onEatSound);
	~SuperPillEaten();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
};
#endif // SUPERPILLEATEN_H