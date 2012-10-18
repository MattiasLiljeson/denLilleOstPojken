#include "InGameState.h"
#include "StateManager.h"
#include "Game.h"
#include <Circle.h>

InGameState::InGameState(StateManager* p_parent, IODevice* p_io, bool p_reset): State(p_parent)
{
	m_io = p_io;
	// Allocation: Moved to onEntry (Added by Jarl 2012-10-15)
	/*
	if (m_io)
	{
		m_factory = new GOFactory(p_io);
		m_tileMap = NULL;
		m_stats = NULL;
		m_currentMap = 1;
		if (p_reset)
			restart();
	}
	
	onEntry(); // alternative
	*/
}
InGameState::~InGameState()
{
	// Deallocation: Moved to onExit (Added by Jarl 2012-10-15)
	/*
	if (m_io)
	{
		for (int i = m_gameObjects.size() - 1; i >= 0; i--)
		{
			delete m_gameObjects.at(i);
		}
		m_gameObjects.clear();
		if (m_tileMap)
			delete m_tileMap;
		if (m_stats)
			delete m_stats;
		if (m_factory)
			delete m_factory;
	}
	*/
	onExit();
}

bool InGameState::onEntry()
{
	if (!m_resourcesAllocated)
	{
		if (m_io)
		{
			m_factory = new GOFactory(m_io);
			m_tileMap = NULL;
			m_stats = NULL;
			m_currentMap = 2;
			m_gui = NULL;
		}
		restart();
		m_resourcesAllocated=true;
	}
	return true;
}

bool InGameState::onExit()
{
	if (m_resourcesAllocated)
	{
		if (m_io)
		{
			for (int i = m_gameObjects.size() - 1; i >= 0; i--)
			{
				delete m_gameObjects.at(i);
			}
			m_gameObjects.clear();
			if (m_tileMap)
				delete m_tileMap;
			if (m_stats)
				delete m_stats;
			if (m_factory)
				delete m_factory;
			if (m_gui)
				delete m_gui;
		}
		m_resourcesAllocated=false;
	}

	return true;
}

void InGameState::update(float p_dt)
{
	if (m_io)
	{
		InputInfo input = m_io->fetchInput();
		
		if (m_stats->getNumPills() < 1)
		{
			m_currentMap = (m_currentMap+1) % 2;
			restart();
			return;
		}

		for (unsigned int index = 0; index < m_gameObjects.size(); index++)
		{
			m_gameObjects[index]->update(p_dt, input);
		};

		checkDynamicCollision();

	
		if (m_stats)
		{
			m_stats->update(p_dt, input);
			if (m_stats->getActivatedItem() == 0)
			{
				Bomb* b = m_factory->CreateBomb(m_avatar->getClosestTile(), m_tileMap); 
				m_bombs.push_back(b);
				m_gameObjects.push_back(b);
			}
		}

		if (m_gui)
			m_gui->update(p_dt);

		int elapsed = (int)m_stats->getGameTimer()->getElapsedTime();

		stringstream ss;

		ss << elapsed;

		string text = "Elapsed Game Time: " + ss.str() + " seconds";

		m_io->setWindowText(text);

		if (input.keys[InputInfo::SPACE] == InputInfo::KEYRELEASED)
		{
			//restart();
			//return;
		}
		//
		if (input.keys[InputInfo::ESC] == InputInfo::KEYRELEASED)
		{
			m_parent->requestStateChange(m_parent->getMenuState());
		}
		/*
		if(input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED || !m_io->isRunning())
		{
			m_parent->terminate();
		}
		*/
		if (m_avatar->isDead())
		{
			m_stats->loseLife();
			if (m_stats->getNumLives() > 0)
				m_avatar->revive(m_startTile);
			else
				m_parent->requestStateChange(m_parent->getMenuState());


		}
	}
}

void InGameState::draw(float p_dt)
{
}

bool InGameState::checkDynamicCollision()
{
	Circle avatarBC(m_avatar->getPostion(), m_avatar->getRadius() / 4);

	bool collision = false;
	for(unsigned int index = 0; index < m_monsters.size(); index++)
	{
		Monster* monster = m_monsters.at(index);
		if (!monster->isDead())
		{
			Circle monsterBC(monster->getPostion(),monster->getRadius() / 4);

			if(avatarBC.collidesWith(monsterBC))
			{
				collision = true;
				if (m_stats->isSuperMode())
				{
					monster->kill();
					m_stats->addScore(MONSTER_KILLED);
				}
				else
					m_avatar->kill();
			}
		}
		for (int bomb = 0; bomb < m_bombs.size(); bomb++)
		{
			if (m_bombs[bomb]->isColliding(monster) && !monster->isDead())
			{
				monster->kill();
				m_stats->addScore(MONSTER_KILLED);
			}
		}
	}
	if (!m_avatar->inAir())
	{
		for(unsigned int index = 0; index < m_traps.size(); index++)
		{
			Trap* trap = m_traps.at(index);
			Circle trapBC(trap->getPostion(),trap->getRadius() / 8);

			if(avatarBC.collidesWith(trapBC))
			{
				collision = true;
				m_avatar->kill();
			}
		}
	}

	return collision;
}
void InGameState::restart()
{
	if (m_io)
	{
		m_io->clearSpriteInfos();
		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			delete m_gameObjects[i];
		}
		m_gameObjects.clear();
		m_monsters.clear();
		m_bombs.clear();
		if (m_tileMap)
			delete m_tileMap;
		if (m_stats)
			delete m_stats;
		if (m_gui)
			delete m_gui;

		m_tileMap	= 0;
		MapLoader mapParser;
		m_stats = new GameStats(m_parent->getNewTimerInstance());

		stringstream ss;
		ss << m_currentMap;
		string mapString = "../Maps/" + ss.str() + ".txt";
		mapParser.parseMap(mapString, m_io, m_stats, m_factory);

		m_tileMap = mapParser.getTileMap();
		m_gameObjects = mapParser.getGameObjects();
		m_avatar = mapParser.getAvatar();
		m_monsters = mapParser.getMonsters();
		m_traps = mapParser.getTraps();
		m_gui = mapParser.getGUI();
		m_startTile = m_avatar->getCurrentTile();
	}
}

void InGameState::handleInput( InputInfo p_input )
{
	if ( p_input.keys[InputInfo::SPACE] == InputInfo::KEYRELEASED )
	{
		//m_parent->requestStateChange(m_parent->getMenuState());
		restart();
		return;
	}
	else if( p_input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED ||
		!m_io->isRunning() )
	{
		m_parent->terminate();
	}
}