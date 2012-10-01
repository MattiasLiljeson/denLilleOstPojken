#include "Game.h"

Game::Game()
{
}


Game::Game(Timer* p_timer, IOContext* p_context)
{
	srand(time(NULL));
	m_timer		= p_timer;
	m_running	= false;
	m_tileMap	= 0;
	m_mapParser = new MapLoader();
	m_gameStats = new GameStats();

	if (p_context)
		m_io = new IODevice(p_context);
	else
		m_io = 0;

	//m_stateManager = new StateManager(m_io);
	//m_stateManager->requestStateChange(m_stateManager->getInGameState());
}

Game::~Game()
{
	for (int i = m_gameObjects.size() - 1; i >= 0; i--)
	{
		GameObject* gameObject = m_gameObjects.at(i);
		m_gameObjects.pop_back();
		delete gameObject;
	}
	if (m_io)
		delete m_io;
	if (m_tileMap)
		delete[] m_tileMap;
	if (m_mapParser)
		delete m_mapParser;
	if (m_gameStats)
		delete m_gameStats;
}

int Game::run()
{
	if (!m_timer || !m_io)
		return 1;

	m_running = true;
	m_timer->start();

	vector<int> data = m_mapParser->parseMap("..\\Maps\\test_map.txt");

	int numPills = 0;

	TileType* types = new TileType[100];
	for (int i = 0; i < 100; i++)
	{
		if (data[i] == TileType::WALL_CENTER)
			types[i] = TileType::WALL_CENTER;
		
		else if(data[i] == TileType::PILL)
		{
			types[i] = TileType::PILL;
			numPills += 1;
		}
		
		else if(data[i] == TileType::AVATAR_SPAWN)
			types[i] = TileType::AVATAR_SPAWN;

		else if(data[i] == TileType::MONSTER_SPAWN)
			types[i] = TileType::MONSTER_SPAWN;
		else
			types[i] = TileType::EMPTY;
	}
	m_tileMap = new Tilemap(10, 10, types, m_io);

	m_gameStats->setNumPills(numPills);

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
				GameObject* avatar = new Avatar(m_io->addSpriteInfo(), m_tileMap, m_tileMap->getTile(TilePosition(j, i)),m_gameStats);
				m_gameObjects.push_back(avatar);
			}
		}
	}
	delete types;

	while (m_running)
	{
		m_timer->tick();
		
		InputInfo input = m_io->fetchInput();

		update( (float)m_timer->getDeltaTime(), input );
		m_io->update(m_timer->getDeltaTime());
		m_io->draw(m_timer->getDeltaTime());

		if( m_gameStats->getNumPills()<1)
			m_running = false;

		if( input.keys[InputInfo::ESC] == InputInfo::KEYDOWN || !m_io->isRunning())
		{
			m_running = false;
		}

	}

	return 0;
}

int Game::update(float p_deltaTime, InputInfo p_inputInfo)
{
	for (unsigned int index = 0; index < m_gameObjects.size(); index++)
	{
		m_gameObjects[index]->update(p_deltaTime, p_inputInfo);
	}
	return 0;
}