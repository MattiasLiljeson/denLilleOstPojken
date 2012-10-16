#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <fstream>
#include <vector>
#include <string>
#include "Tilemap.h"
#include "State.h"
#include "GOFactory.h"

using namespace std;


enum TileTypes
{
	//All equals or below 90 will be regard as walls
	WALLS = 90,
	//All equals or below  will be regard as paths
	PATHS = 180,
	//All equals or below  will be regard as SWITCHES
	SWITCHES = 210,
	//All equals or below  will be regard as WALLSWITCHES
	WALLSWITCHES = 240,
	//The chess-boy spawn
	CBSPAWN = 271,
	//All equals or below  will be regard as EnemieSpawn
	ENEMIESPAWN = 330,
	//All equals or below  will be regard as Buffs
	BUFFS = 390,
	//All equals or below  will be regard as Item
	ITEMS = 420,
	//All equals or below  will be regard as EatAblePowerUps
	EATPOWERUP = 450,
	//All equals or below  will be regard as Traps
	TRAPS = 480
};
class MapLoader
{
private:
	Tilemap* m_tileMap;
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
	vector<Trap*> getTraps();
	GUI*			getGUI();
};

#endif
