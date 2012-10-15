#ifndef BASICIDLE_H
#define BASICIDLE_H

#include "GOState.h"

class BasicIdle: public GOState
{
private:
public:
	BasicIdle(GameObject* p_gameObject);
	virtual ~BasicIdle();
	int onEnter();
	int onExit();
	int update(float p_dt, InputInfo p_inputInfo);
};

#endif