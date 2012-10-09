#ifndef GOFACTORY_H
#define GOFACTORY_H

#include "IODevice.h"
#include "Avatar.h"
#include "Monster.h"
#include "Tilemap.h"
#include "SuperPill.h"
#include "SpeedPill.h"
#include "Pill.h"
#include <fVector3.h>

class GOFactory
{
private:
	IODevice* m_io;

private:
	SpriteInfo* CreateSpriteInfo(string p_texture, fVector3 p_position, fVector2 p_size, Rect* p_sourceRect);
public:
	GOFactory(IODevice* p_io);
	Avatar* CreateAvatar(Tilemap* p_map, Tile* p_startTile, GameStats* p_stats);
	Monster* CreateMonster(Tile* p_tile, Tilemap* p_map);
	SuperPill* CreateSuperPill(Tile* p_tile, GameStats* p_gameStats);
	SpeedPill* CreateSpeedPill(Tile* p_tile, GameStats* p_gameStats);
	Pill* CreatePill(Tile* p_tile, GameStats* p_gameStats);
};

#endif