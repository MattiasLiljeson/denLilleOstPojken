#ifndef TMFACTORY_H
#define TMFACTORY_H

#include "IODevice.h"
#include "TileTypes.h"
#include "Tilemap.h"
#include "Tile.h"
#include <SpriteInfo.h>
#include <string>
#include <fVector3.h>
#include <fVector2.h>
#include <vector>

using namespace std;

class GOFactory;

class TMFactory
{
private:
	IODevice*	m_io;
	GOFactory*	m_GOFactory;
	int			m_theme;
	string		m_currentTileMap;
public:
	TMFactory(IODevice* p_io, GOFactory* p_GOFactory);
	~TMFactory();
	Tilemap*	CreateTileMap(int p_theme, int p_width, int p_height, vector<int> p_mapData);
	Tile*		CreateSingleTile(int p_type, TilePosition p_position, 
				int p_tileSizeX, int p_tileSizeY);
	Tile*		CreateWallTile(int p_type, TilePosition p_position,
				int p_tileSizeX, int p_tileSizeY);
	Tile*		CreatePathTile(int p_type, TilePosition p_position,
				int p_tileSizeX, int p_tileSizeY);
	Tile*		CreateBasicWalkableTile(TilePosition, int , int );
	Tile*		CreateWallSwitch(int p_type, TilePosition,	int , int );
};

#endif