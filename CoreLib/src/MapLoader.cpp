#include "MapLoader.h"

MapLoader::MapLoader()
{
	m_avatar = NULL;
}

MapLoader::~MapLoader()
{
}

int MapLoader::parseMap(string p_MapPath, IODevice* p_io, GameStats* p_stats)
{
	m_stats = p_stats;
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

		m_tileMap = new Tilemap(width, height, types, p_io);
		delete[] types;

		int currentSwitch = 0;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int index = i*width+j;
				if (m_map[index] == PILL)
				{
					m_gameObjects.push_back(new Pill(p_io, m_tileMap->getTile(TilePosition(j, i)), m_stats));
				}
				else if (m_map[index] == SPEEDPILL)
				{
					m_gameObjects.push_back(new SpeedPill(p_io, m_tileMap->getTile(TilePosition(j, i)), m_stats));
				}
				else if (m_map[index] == SWITCH)
				{
					vector<TilePosition> targets = switches[currentSwitch++];
					m_gameObjects.push_back(new Switch(p_io, m_tileMap->getTile(TilePosition(j, i)), m_tileMap, m_stats, targets));

				}
				else if (m_map[index] == MONSTER_SPAWN)
				{
					Monster* monster = new Monster(m_tileMap->getTile(TilePosition(j, i)), m_tileMap, p_io);
					m_monsters.push_back(monster);
					m_gameObjects.push_back(monster);
				}
				else if (m_map[index] == AVATAR_SPAWN)
				{
					m_avatar = new Avatar(p_io, m_tileMap, m_tileMap->getTile(TilePosition(j, i)), m_stats);
					m_gameObjects.push_back(m_avatar);

				}
				else if (m_map[index] == SUPERPILL)
				{
					m_gameObjects.push_back(new SuperPill(p_io, m_tileMap->getTile(TilePosition(j,i)), m_stats));
				}
			}
		}

		if(!m_avatar)
			return GAME_FAIL;

		for (int i = 0; i < m_monsters.size(); i++)
		{
			m_monsters[i]->addMonsterAI(m_avatar, m_stats, m_tileMap);
		}
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
