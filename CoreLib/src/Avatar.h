#ifndef AVATAR_H
#define AVATAR_H

#include "GameObject.h"
#include "TransformInfo.h"

class Avatar : public GameObject
{
private:

public:
	Avatar();
	Avatar(SpriteInfo* p_spriteInfo);

	void update(float p_deltaTime, InputInfo p_inputInfo);
};

#endif