#include "WallSwitch.h"

WallSwitch::WallSwitch(SpriteInfo* p_spriteInfo, Tile* p_tile) : GameObject(p_spriteInfo)
{
	m_spriteInfo	= p_spriteInfo;
	m_tile			= p_tile;
	m_spriteInfo->visible = false;

	switchState();
}

void WallSwitch::update(float p_deltaTime, InputInfo p_inputInfo)
{

}

void WallSwitch::switchState()
{
	if(m_spriteInfo->visible)
	{
		m_spriteInfo->visible = false;
		m_tile->setWalkAble(true);
	}
	else
	{
		m_spriteInfo->visible = true;
		m_tile->setWalkAble(false);
	}

}