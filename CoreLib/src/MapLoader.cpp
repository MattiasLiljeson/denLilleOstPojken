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

	if (!m_factory)
		return GAME_FAIL;

	fstream file(p_MapPath.c_str());

	int value;
	int switchCount = 0;

	if(file)
	{
		int width;
		int height;
		file >> width;
		file >> height;
		vector<int> m_map = vector<int>(width*height);
		for(int i = height - 1; i >= 0; i--)
		{
			for (int j = 0; j < width; j++)
			{
				file >> value;
				m_map[i*width+j] = value;
				if (value == SWITCH)
					switchCount++;
			}
		}

		vector<vector<TilePosition>> switches; 
		int x, y;
		for (int i = 0; i < switchCount; i++)
		{
			switches.push_back(vector<TilePosition>());
			int affected;
			file >> affected;
			for (int j = 0; j < affected; j++)
			{
				file >> x;
				file >> y;
				switches.back().push_back(TilePosition(x, y));
			}
		}

		bool* types = new bool[width*height];
		for (int i = 0; i < width*height; i++)
		{
			if (m_map[i] == WALL_CENTER)
				types[i] = false;
			else
				types[i] = true;

		}

		m_tileMap = m_factory->CreateTileMap(width, height, types);
		delete[] types;

		int currentSwitch = 0;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int index = i*width+j;
				if (m_map[index] == PILL)
				{
					m_gameObjects.push_back(m_factory->CreatePill(
						m_tileMap->getTile(TilePosition(j, i)), m_stats));
				}
				else if (m_map[index] == SPEEDPILL)
				{
					m_gameObjects.push_back(m_factory->CreateSpeedPill(
						m_tileMap->getTile(TilePosition(j, i)), m_stats));
				}
				else if (m_map[index] == SWITCH)
				{
					vector<TilePosition> targets = switches[currentSwitch++];
					m_gameObjects.push_back(m_factory->CreateSwitch(
						m_tileMap->getTile(TilePosition(j, i)),
						m_tileMap, m_stats, targets));

				}
				else if (m_map[index] == MONSTER_SPAWN)
				{
					Monster* monster = m_factory->CreateMonster(
						m_tileMap->getTile(TilePosition(j, i)), m_tileMap);
					m_monsters.push_back(monster);
					m_gameObjects.push_back(monster);
				}
				else if (m_map[index] == AVATAR_SPAWN)
				{
					m_avatar = m_factory->CreateAvatar(m_tileMap,
						m_tileMap->getTile(TilePosition(j, i)), m_stats);
					m_gameObjects.push_back(m_avatar);

				}
				else if (m_map[index] == SUPERPILL)
				{
					m_gameObjects.push_back(m_factory->CreateSuperPill(
						m_tileMap->getTile(TilePosition(j,i)), m_stats));
				}
				else if (m_map[index] == TRAP)
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

		for (int i = 0; i < m_monsters.size(); i++)
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
