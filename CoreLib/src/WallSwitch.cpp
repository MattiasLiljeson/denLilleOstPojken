#include "WallSwitch.h"

WallSwitch::WallSwitch(SpriteInfo* p_spriteInfo, Tile* p_tile) : GameObject(p_spriteInfo)
{
	m_spriteInfo	= p_spriteInfo;
	m_tile			= p_tile;

	switchState();
}

void WallSwitch::update(float p_deltaTime, InputInfo p_inputInfo)
{

}

void WallSwitch::switchState()
{
	if(m_tile->getType() == false)	// Not walkable.
	{
		//m_spriteInfo->visible = false;
		m_spriteInfo->textureRect.x = 64;
		m_tile->setWalkAble(true);
	}
	else
	{
		//m_spriteInfo->visible = true;
		m_spriteInfo->textureRect.x = 0;
		m_tile->setWalkAble(false);
	}

}