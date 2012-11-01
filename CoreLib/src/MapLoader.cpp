#include "MapLoader.h"

MapLoader::MapLoader()
{
	m_avatar = NULL;
}

MapLoader::~MapLoader()
{
}

int MapLoader::parseMap(string p_MapPath, IODevice* p_io, GameStats* p_stats,
	GOFactory* p_factory)
{
	m_factory = p_factory;
	m_stats = p_stats;
	m_avatar	= NULL;
	m_tileMap	= NULL;
	m_gui		= NULL;


	if (!m_factory)
		return GAME_FAIL;

	fstream file(p_MapPath.c_str());

	int value;
	m_theme = m_width = m_height = 0;
	char comma;
	vector<vector<TilePosition>> switches(8);
	if(file)
	{
		//Begining the parsing of the map
		parseHead(file);

		//Inverting the map layout
		vector<int> map = vector<int>(m_width*m_height);
		for(int i = m_height - 1; i >= 0; i--)
		{
			for (int j = 0; j < m_width; j++)
			{
				file >> value;
				file >> comma;
				map[i*m_width+j] = value;
				if (value > SWITCHES && value <= WALLSWITCHES)
					switches.at(value-(SWITCHES+1)).push_back(TilePosition(j,i));
			}
		}

		m_tileMap = m_factory->CreateTileMap(m_theme, m_width, m_height, map);
		
		vector<vector<Switch*>> newSwitches(8);
		for(unsigned int i = 0; i < newSwitches.size(); i++)
			newSwitches[i] = vector<Switch*>();

		vector<vector<WallSwitch*>> newWallSwitches(8);
		for(unsigned int i = 0; i < newWallSwitches.size(); i++)
			newWallSwitches[i] = vector<WallSwitch*>();
		
		//Create the gameobjects from the information recently parsed from the map
		/**/for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_width; j++)
			{
				int index = i*m_width+j;
				if (map[index] > WALLS && map[index] <= PATHS)
				{
					m_gameObjects.push_back(m_factory->CreatePill(
											m_tileMap->getTile(TilePosition(j, i)), m_stats));
				}
				else if (map[index] > ENEMIESPAWN && map[index] <= BUFFS)
				{
					m_gameObjects.push_back(m_factory->CreateSpeedPill(
											m_tileMap->getTile(TilePosition(j, i)), m_stats));
				}
				else if (map[index] > PATHS && map[index] <= SWITCHES)
				{
					Switch* newSwitch = m_factory->CreateSwitch(
											m_tileMap->getTile(TilePosition(j, i)),
											m_stats, vector<WallSwitch*>(), map[index]);
					int switchIndex = map[index] - (PATHS+1);
					newSwitches[switchIndex].push_back(newSwitch);
					m_gameObjects.push_back(newSwitch);
				}
				else if (map[index] > SWITCHES && map[index] <= WALLSWITCHES)
				{
					WallSwitch* newWallSwitch = m_factory->CreateWallSwitch(
						m_tileMap->getTile(TilePosition(j,i)),map[index]);
					int wallSwitchIndex = map[index] - (SWITCHES+1);
					newWallSwitches.at(wallSwitchIndex).push_back(newWallSwitch);
					m_gameObjects.push_back(newWallSwitch);
				}
				else if (map[index] > CBSPAWN && map[index] <= ENEMIESPAWN )
				{
					Monster* monster = m_factory->CreateMonster(
						m_tileMap->getTile(TilePosition(j, i)), m_tileMap,m_stats, map[index]);
					m_monsters.push_back(monster);
					m_gameObjects.push_back(monster);
				}
				else if (map[index] == CBSPAWN)
				{
					m_avatar = m_factory->CreateAvatar(m_tileMap,
												m_tileMap->getTile(TilePosition(j, i)), m_stats);
					m_gameObjects.push_back(m_avatar);
				}
				else if (map[index] > BUFFS && map[index] <= ITEMS)
				{
					m_gameObjects.push_back(m_factory->CreateBombPill(
											m_tileMap->getTile(TilePosition(j,i)), m_stats));
				}
				else if (map[index] > ITEMS && map[index] <= EATPOWERUP)
				{
					m_gameObjects.push_back(m_factory->CreateSuperPill(
											m_tileMap->getTile(TilePosition(j,i)), m_stats));
				}
				else if (map[index] > EATPOWERUP && map[index] <= TRAPS)
				{
					Trap* trap = m_factory->CreateTrap(
											m_tileMap->getTile(TilePosition(j, i)), m_tileMap);
					m_traps.push_back(trap);
					m_gameObjects.push_back(trap);
				}
			}
		}

		if(!m_avatar)
			return GAME_FAIL;

		for (unsigned int i = 0; i < newSwitches.size(); i++)
		{
			for (unsigned int j = 0; j < newSwitches[i].size(); j++)
			{
				newSwitches[i].at(j)->setTargets(newWallSwitches.at(i));
			}
		}

		for (unsigned int i = 0; i < m_monsters.size(); i++)
		{
			m_monsters[i]->addMonsterAI(m_avatar, m_stats, m_tileMap);
		}

		m_gui = m_factory->CreateGUI(m_stats);

		return GAME_OK;
	}
	
	return GAME_FAIL;
}
Tilemap* MapLoader::getTileMap()
{
	return m_tileMap;
}
vector<GameObject*> MapLoader::getGameObjects()
{
	return m_gameObjects;
}
Avatar* MapLoader::getAvatar()
{
	return m_avatar;
}
vector<Monster*> MapLoader::getMonsters()
{
	return m_monsters;
}	
vector<Trap*> MapLoader::getTraps()
{
	return m_traps;
}
GUI* MapLoader::getGUI()
{
	return m_gui;
}
void MapLoader::parseHead(fstream &p_file)
{
	string temp;
	char dummy = 't';
	
	p_file >> temp;
	while (dummy != '=')
		p_file >> dummy;
	p_file >> m_width;
	dummy = 't';
	
	while (dummy != '=')
		p_file >> dummy;
	p_file >> m_height;

	p_file >> temp;
	p_file >> temp;
	p_file >> temp;

	p_file >> m_theme;

	for(int i = m_height - 1; i >= 0; i--)
	{
		p_file >> temp;
	}

	p_file >> temp;
	p_file >> temp;
	p_file >> temp;
}
