#ifndef MAPLOADER_H
#define MAPLOADER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Tilemap.h"
#include "State.h"

using namespace std;

enum TileType
{
	EMPTY,
	WALL_CENTER,
	PILL,
	AVATAR_SPAWN,
	MONSTER_SPAWN,
	SPEEDPILL,
	SUPERPILL,
	SWITCH
};

class MapLoader
{
private:
	Tilemap* m_tileMap;
	vector<GameObject*>	m_gameObjects;
	GameStats* m_stats;

public:
	MapLoader();
	virtual ~MapLoader();
	
	void parseMap(string p, IODevice* p_io, GameStats* p_stats);
	Tilemap* getTileMap();
	vector<GameObject*> getGameObjects();
};

#endif