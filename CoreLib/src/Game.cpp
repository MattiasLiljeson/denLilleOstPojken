#include "Game.h"

Game::Game()
{
}


Game::Game(Timer* p_timer, IOContext* p_context)
{
	srand((unsigned int)time(NULL));
	m_timer		= p_timer;
	m_running	= false;
<<<<<<< HEAD
=======
	m_tileMap	= 0;
	m_mapParser = new MapLoader();
	m_gameStats = new GameStats();
>>>>>>> origin/s2t20_Count_Pills_new

	if (p_context)
		m_io = new IODevice(p_context);
	else
		m_io = 0;

	m_stateManager = new StateManager(m_io);
}

Game::~Game()
{
	delete m_stateManager;
	delete m_io;
}

int Game::run()
{
	m_running = true;
	m_timer->start();

	while (m_running)
	{
		if (m_stateManager->isTerminated())
			break;
		m_timer->tick();

		m_stateManager->update((float)m_timer->getDeltaTime());
		m_io->update((float)m_timer->getDeltaTime());
		m_io->draw((float)m_timer->getDeltaTime());

		
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