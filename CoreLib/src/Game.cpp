#include "Game.h"

Game::Game()
{
}

Game::Game(Timer* p_timer, IIOContext* p_context)
{
	m_timer		= p_timer;
	m_running	= false;
	
	if (p_context)
		m_io = new IODevice(p_context);
	else
		m_io = 0;
}

int Game::run()
{
	if (!m_timer || !m_io)
		return 1;

	m_running = true;
	m_timer->start();




	while (m_running)
	{
		m_timer->tick();
		
		update( (float)m_timer->getDeltaTime(), m_io->fetchInput() );
		m_io->draw();
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

Game::~Game()
{
	if (m_timer)
		delete m_timer;
	if (m_io)
		delete m_io;
}

int Game::foo()
{
	return 7;
}