#include "InGameState.h"
#include "StateManager.h"
#include "Game.h"

InGameState::InGameState(StateManager* p_parent, IODevice* p_io): State(p_parent)
{
	m_io = p_io;
	vector<int> data = m_mapParser->parseMap("..\\Maps\\test_map.txt");

	TileType* types = new TileType[100];
	for (int i = 0; i < 100; i++)
	{
		if (data[i] == TileType::WALL_CENTER)
			types[i] = TileType::WALL_CENTER;
		
		else if(data[i] == TileType::PILL)
			types[i] = TileType::PILL;
		
		else if(data[i] == TileType::AVATAR_SPAWN)
			types[i] = TileType::AVATAR_SPAWN;

		else if(data[i] == TileType::MONSTER_SPAWN)
			types[i] = TileType::MONSTER_SPAWN;
		else
			types[i] = TileType::EMPTY;
	}
	m_tileMap = new Tilemap(10, 10, types, m_io);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (types[i*10+j] == TileType::PILL)
			{
				m_gameObjects.push_back(new Pill(m_io->addSpriteInfo(), m_tileMap->getTile(TilePosition(j, i))));
			}
			if (types[i*10+j] == TileType::MONSTER_SPAWN)
			{
				m_gameObjects.push_back(new Monster(m_tileMap->getTile(TilePosition(j, i)), m_tileMap, m_io->addSpriteInfo()));
			}
			if (types[i*10+j] == TileType::AVATAR_SPAWN)
			{
				//GameObject* avatar = new Avatar(m_io->addSpriteInfo(), m_tileMap, m_tileMap->getTile(TilePosition(j, i)));
				//m_gameObjects.push_back(avatar);
			}
		}
	}
	delete types;
}
void InGameState::update(float p_dt)
{
}
void InGameState::draw(float p_dt)
{
}