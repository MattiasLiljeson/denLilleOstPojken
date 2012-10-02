#include "InGameState.h"
#include "StateManager.h"
#include "Game.h"
#include <Circle.h>

InGameState::InGameState(StateManager* p_parent, IODevice* p_io): State(p_parent)
{
	m_io = p_io;
	if (m_io)
	{
		m_tileMap	= 0;
		m_mapParser = new MapLoader();
		m_stats = new GameStats(m_parent->getNewTimerInstance());
		vector<int> data = m_mapParser->parseMap("..\\Maps\\test_map.txt");
		int mapWidth = m_mapParser->getLoadedWidth();
		int mapHeight = m_mapParser->getLoadedHeight();

		bool* types = new bool[mapWidth*mapHeight];
		for (int i = 0; i < mapWidth*mapHeight; i++)
		{
			if (data[i] == WALL_CENTER)
				types[i] = false;
			else
				types[i] = true;

		}

		m_tileMap = new Tilemap(mapWidth, mapHeight, types, m_io);

		for (int i = 0; i < mapHeight; i++)
		{
			for (int j = 0; j < mapWidth; j++)
			{
				if (data[i*mapWidth+j] == PILL)
				{
					m_gameObjects.push_back(new Pill(m_io, m_tileMap->getTile(TilePosition(j, i)), m_stats));
				}
				else if (data[i*mapWidth+j] == SPEEDPILL)
				{
					m_gameObjects.push_back(new SpeedPill(m_io, m_tileMap->getTile(TilePosition(j, i)), m_stats));
				}
				else if (data[i*mapWidth+j] == SWITCH)
				{
					m_gameObjects.push_back(new Switch(m_io, m_tileMap->getTile(TilePosition(j, i)), m_tileMap, m_stats));

				}
				else if (data[i*mapWidth+j] == MONSTER_SPAWN)
				{
					Monster* monster = new Monster(m_tileMap->getTile(TilePosition(j, i)), m_tileMap, m_io);
					m_monsters.push_back(monster);
					m_gameObjects.push_back(monster);
				}
				else if (data[i*mapWidth+j] == AVATAR_SPAWN)
				{
					m_avatar = new Avatar(m_io, m_tileMap, m_tileMap->getTile(TilePosition(j, i)), m_stats);
					m_gameObjects.push_back(m_avatar);
				}
				else if (data[i*mapWidth+j] == SUPERPILL)
				{
					m_gameObjects.push_back(new SuperPill(m_io, m_tileMap->getTile(TilePosition(j,i)), m_stats));
				}
			}
		}
		delete types;
	}
}
InGameState::~InGameState()
{
	if (m_io)
	{
		for (int i = m_gameObjects.size() - 1; i >= 0; i--)
		{
			GameObject* gameObject = m_gameObjects.at(i);
			m_gameObjects.pop_back();
			delete gameObject;
		}
		if (m_tileMap)
			delete[] m_tileMap;
		if (m_mapParser)
			delete m_mapParser;
		if (m_stats)
			delete m_stats;
	}
}
void InGameState::update(float p_dt)
{
	if (m_io)
	{
		InputInfo input = m_io->fetchInput();

		if (input.keys[InputInfo::SPACE] == InputInfo::KEYPRESSED)
			m_parent->requestStateChange(m_parent->getMenuState());
		if(input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED || !m_io->isRunning())
		{
			m_parent->terminate();
		}
		if (m_stats->getNumPills() < 1)
			m_parent->terminate();

		for (unsigned int index = 0; index < m_gameObjects.size(); index++)
		{
			m_gameObjects[index]->update(p_dt, input);
		};

		for (unsigned int index = 0; index < m_gameObjects.size(); index++)
		{
			m_gameObjects[index]->update(p_dt, input);
		};

		checkDynamicCollision();
	
		m_stats->update(p_dt);
	}
}
void InGameState::draw(float p_dt)
{
}

bool InGameState::checkDynamicCollision()
{
	Circle avatarBC(m_avatar->getPostion(), m_avatar->getRadius());

	bool collision = false;
	for(unsigned int index = 0; index < m_monsters.size(); index++)
	{
		Monster* monster = m_monsters.at(index);
		if (!monster->isDead())
		{
			Circle monsterBC(monster->getPostion(),monster->getRadius());

			if(avatarBC.collidesWith(monsterBC))
			{
				if (m_stats->isSuperMode())
				{
					monster->kill();
					collision = true;
				}
				else
					m_parent->terminate();
			}
		}
	}

	return collision;
}