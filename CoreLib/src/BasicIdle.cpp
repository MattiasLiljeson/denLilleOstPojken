#include "BasicIdle.h"


BasicIdle::BasicIdle(GameObject* p_gameObject) : GOState(p_gameObject)
{

}

BasicIdle::~BasicIdle()
{

}

int BasicIdle::onEnter()
{
	return GAME_OK;	
}

int BasicIdle::onExit()
{
	return GAME_OK;
}

int BasicIdle::update(float p_dt, InputInfo p_inputInfo)
{
	return GAME_OK;
}