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
	SpriteInfo spriteInfo;
	spriteInfo.transformInfo.translation[TransformInfo::X] = 300;
	spriteInfo.transformInfo.translation[TransformInfo::Y] = 300;
	spriteInfo.transformInfo.scale[TransformInfo::X] = 100;
	spriteInfo.transformInfo.scale[TransformInfo::Y] = 100;

	m_io->addSpriteInfo(spriteInfo);

	spriteInfo.textureFileName = "..\\Textures\\pacman-1974.png";
	spriteInfo.transformInfo.translation[TransformInfo::X] = 200;
	spriteInfo.transformInfo.translation[TransformInfo::Y] = 500;
	spriteInfo.transformInfo.scale[TransformInfo::X] = 50;
	spriteInfo.transformInfo.scale[TransformInfo::Y] = 50;
	
	m_io->addSpriteInfo(spriteInfo);
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