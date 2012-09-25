#include "Game.h"

Game::Game()
{
}

Game::Game(Timer* p_timer, IOContext* p_context)
{
	m_timer		= p_timer;
	m_running	= false;
	
	if (p_context)
		m_io = new IODevice(p_context);
	else
		m_io = 0;
}

Game::~Game()
{
	if (m_io)
		delete m_io;
}

int Game::run()
{
	if (!m_timer || !m_io)
		return 1;

	m_running = true;
	m_timer->start();

	/* Ugli code */
	/*SpriteInfo spriteInfo;
	spriteInfo.transformInfo.translation[TransformInfo::X] = 300;
	spriteInfo.transformInfo.translation[TransformInfo::Y] = 300;
	spriteInfo.transformInfo.scale[TransformInfo::X] = 100;
	spriteInfo.transformInfo.scale[TransformInfo::Y] = 100;

	m_io->addSpriteInfo(spriteInfo);

	spriteInfo.transformInfo.translation[TransformInfo::X] = 200;
	spriteInfo.transformInfo.translation[TransformInfo::Y] = 500;
	spriteInfo.transformInfo.scale[TransformInfo::X] = 50;
	spriteInfo.transformInfo.scale[TransformInfo::Y] = 50;
	
	m_io->addSpriteInfo(spriteInfo);*/

	int arr[] = 
				{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
				 1, 2, 2, 2, 2, 2, 2, 2, 2, 1,
				 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 
				 1, 2, 2, 2, 2, 2, 2, 2, 2, 1,
				 1, 2, 1, 2, 1, 1, 2, 1, 2, 1, 
				 1, 2, 1, 2, 2, 2, 2, 1, 2, 1,
				 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 
				 1, 2, 1, 1, 2, 1, 1, 1, 2, 1,
				 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 
				 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	TileType* types = new TileType[100];
	for (int i = 0; i < 100; i++)
	{
		if (arr[i] == 1)
			types[i] = TileType::WALL_TILE;
		else
			types[i] = TileType::FREE_TILE;
	}
	m_tileMap = new Tilemap(10, 10, types, m_io);

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (arr[i*10+j] == 2)
				m_pills.push_back(Pill(m_io->addSpriteInfo(), m_tileMap->getTile(TilePosition(j, i))));
		}
	}
	/* End ugli code */

	while (m_running)
	{
		m_timer->tick();
		
		// update( (float)m_timer->getDeltaTime(), m_io->fetchInput() );
		m_io->update(m_timer->getDeltaTime());
		m_io->draw(m_timer->getDeltaTime());

		if( m_io->fetchInput().keys[InputInfo::ESC] == InputInfo::KEYDOWN || !m_io->isRunning())
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
		m_gameObjects[index].update(p_deltaTime, p_inputInfo);
	}
	return 0;
}