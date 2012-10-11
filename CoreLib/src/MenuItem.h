#ifndef MENUITEM_H
#define MENUITEM_H

// HACK: Change to factory..
#include "GameObject.h"
#include "IODevice.h"
#include <string>
using namespace std;

class MenuItem: public GameObject
{
public:
	MenuItem(SpriteInfo* p_spriteInfo);
	virtual ~MenuItem();

	void update(float p_deltaTime, InputInfo p_inputInfo);

};

#endif