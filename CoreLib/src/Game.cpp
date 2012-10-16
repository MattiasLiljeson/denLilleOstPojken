#include "Game.h"

Game::Game()
{
}


Game::Game(Timer* p_timer, IOContext* p_context)
{
	srand((unsigned int)time(NULL));
	m_timer		= p_timer;
	m_running	= false;

	if (p_context)
		m_io = new IODevice(p_context);
	else
		m_io = 0;

	m_stateManager = new StateManager(m_io, p_timer);
}

Game::~Game()
{
	delete m_stateManager;
	delete m_io;
	//delete m_timer;
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

	}

	return 0;
}
