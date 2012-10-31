#include "GameOverState.h"
#include "StateManager.h"
#include <ToString.h>

GameOverState::GameOverState(StateManager* p_parent, IODevice* p_io) : State(p_parent)
{
	m_io = p_io;
}

GameOverState::~GameOverState()
{

}

void GameOverState::initGameOverItems()
{
	float fw = 1.0f/1920.0f;
	float fh = 1.0f/1080.0f;
	string text = "GAME OVER";

	m_gameOverText = m_factory->createMenuItem( 
		fVector3(0.5f, 0.6f, 0.9f), fVector2(fh*600.0f, fh*64.0f),
		text, fVector2(0.0f, 0.0f), fVector2(fw*32, fh*32),"");

	text = "FINAL SCORE: " + toString(m_parent->getCommonResources()->totalScore);
	m_scoreText = m_factory->createMenuItem( 
		fVector3(0.5f, 0.4f, 0.9f), fVector2(fh*600.0f, fh*64.0f),
		text, fVector2(0.0f, 0.0f), fVector2(fw*32, fh*32),"");

	text = "PRESS ENTER TO CONTINUE!";
	m_continueText = m_factory->createMenuItem(
		fVector3(0.5f, 0.2f, 0.9f), fVector2(fh*600.0f, fh*64.0f),
		text, fVector2(0.0f, 0.0f), fVector2(fw*32, fh*32),"");
}

bool GameOverState::onEntry()
{
	if (!m_resourcesAllocated) // only allocate once
	{
		if (m_io)
		{
			m_factory = new GOFactory(m_io);
			m_io->clearSpriteInfos();
			if (m_factory)
				initGameOverItems();
		}
		m_resourcesAllocated = true;
	}
	return true;
}

bool GameOverState::onExit()
{
	if (m_resourcesAllocated) // only deallocate if allocated
	{
		if (m_io)
		{
			delete m_gameOverText;
			delete m_scoreText;
			delete m_factory;		
			m_io->clearSpriteInfos();
		}
		//
		m_resourcesAllocated=false;
	}
	return true;
}

void GameOverState::update(float p_dt)
{
	if (m_io)
	{
		InputInfo input = m_io->fetchInput();

		if (input.keys[InputInfo::ESC]   == InputInfo::KEYRELEASED	|| 
			input.keys[InputInfo::ENTER] == InputInfo::KEYRELEASED	||
			input.keys[InputInfo::SPACE] == InputInfo::KEYRELEASED	||
			!m_io->isRunning())
		{
			m_parent->requestStateChange(m_parent->getMenuState());
		}
	}
}

void GameOverState::draw (float p_dt){}