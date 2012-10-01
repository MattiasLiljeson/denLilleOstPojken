#include "InGameState.h"
#include "StateManager.h"
#include "Game.h"

InGameState::InGameState(StateManager* p_parent, IODevice* p_io): State(p_parent)
{
	m_tileMap	= 0;
	m_mapParser = new MapLoader();

	m_io = p_io;
	vector<int> data = m_mapParser->parseMap("..\\Maps\\test_map.txt");

	TileType* types = new TileType[100];
	for (int i = 0; i < 100; i++)
	{
		if (data[i] == WALL_CENTER)
			types[i] = WALL_CENTER;
		
		else if(data[i] == PILL)
			types[i] = PILL;
		
		else if(data[i] == AVATAR_SPAWN)
			types[i] = AVATAR_SPAWN;

		else if(data[i] == MONSTER_SPAWN)
			types[i] = MONSTER_SPAWN;
		else
			types[i] = EMPTY;
	}
	m_tileMap = new Tilemap(10, 10, types, m_io);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (types[i*10+j] == PILL)
			{
				m_gameObjects.push_back(new Pill(m_io->addSpriteInfo(), m_tileMap->getTile(TilePosition(j, i))));
			}
			if (types[i*10+j] == MONSTER_SPAWN)
			{
				m_gameObjects.push_back(new Monster(m_tileMap->getTile(TilePosition(j, i)), m_tileMap, m_io->addSpriteInfo()));
			}
			if (types[i*10+j] == AVATAR_SPAWN)
			{
				//GameObject* avatar = new Avatar(m_io->addSpriteInfo(), m_tileMap, m_tileMap->getTile(TilePosition(j, i)));
				//m_gameObjects.push_back(avatar);
			}
		}
	}
	delete types;
}
InGameState::~InGameState()
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
}
void InGameState::update(float p_dt)
{
	InputInfo input = m_io->fetchInput();

	if (input.keys[InputInfo::SPACE] == InputInfo::KEYPRESSED)
		m_parent->requestStateChange(m_parent->getMenuState());
	if( input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED || !m_io->isRunning())
	{
		m_parent->terminate();
	}
	for (unsigned int index = 0; index < m_gameObjects.size(); index++)
	{
		m_gameObjects[index]->update(p_dt, input);
	};
}
void InGameState::draw(float p_dt)
{
}