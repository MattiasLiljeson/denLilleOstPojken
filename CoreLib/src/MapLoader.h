#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <fstream>
#include <vector>
#include <string>
#include "Tilemap.h"
#include "State.h"
#include "GOFactory.h"
#include "TileTypes.h"
#include "Switch.h"

using namespace std;


class MapLoader
{
private:
	Tilemap*			m_tileMap;
	vector<GameObject*>	m_gameObjects;
	Avatar*				m_avatar;
	vector<Monster*>	m_monsters;
	vector<Trap*>		m_traps;
	GameStats*			m_stats;
	GUI*				m_gui;
	GOFactory*			m_factory;
	int					m_theme, 
						m_width, 
						m_height;
private:
	void parseHead(fstream &p_file);
public:
	MapLoader();
	virtual ~MapLoader();
	
	int parseMap(string p, IODevice* p_io, GameStats* p_stats, GOFactory* p_factory);
	Tilemap* getTileMap();
	vector<GameObject*> getGameObjects();
	Avatar* getAvatar();
	vector<Monster*> getMonsters();
	vector<Trap*>	getTraps();
	GUI*			getGUI();
};

#endif
