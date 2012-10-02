#ifndef MAPLOADER_H
#define MAPLOADER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Tile.h"

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
	int m_width;
	int m_height;

	vector<int> m_map;
	vector<vector<TilePosition>> m_switches; 

public:
	MapLoader();
	virtual ~MapLoader();
	
	void parseMap(string p);
	int getLoadedWidth();
	int getLoadedHeight();
	vector<int> getMap();
	vector<TilePosition> getSwitch(int p_index);
};

#endif