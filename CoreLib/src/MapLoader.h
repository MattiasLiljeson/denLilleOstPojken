#ifndef MAPLOADER_H
#define MAPLOADER_H


#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
public:
	MapLoader();
	virtual ~MapLoader();
	
	vector<int> parseMap(string p);
	int getLoadedWidth();
	int getLoadedHeight();
};

#endif