#ifndef WALLSWITCH_H
#define WALLSWITCH_H

#include "Tile.h"
#include "Tilemap.h"
#include "GameObject.h"

class WallSwitch : public GameObject
{
private:
	Tilemap*	m_tilemap;
	Tile*		m_tile;
	SpriteInfo* m_spriteInfo;
public:
	WallSwitch(SpriteInfo* p_spriteInfo, Tile* p_tile);
	void update(float p_deltaTime, InputInfo p_inputInfo);
	void switchState();
};

#endif