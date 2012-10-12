#ifndef GOSTATE_H
#define GOSTATE_H

#include <CommonUtility.h>
#include "GameObject.h"

class GOState
{
protected:
	GameObject* m_gameObject;
public:
	GOState(GameObject* p_gameObject);
	virtual int onEnter() = 0;
	virtual int onExit() = 0;
	virtual int update(float p_dt, InputInfo p_inputInfo) = 0;
};

#endif