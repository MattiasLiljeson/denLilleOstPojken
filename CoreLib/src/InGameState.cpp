#include "InGameState.h"
#include "StateManager.h"
#include "Game.h"
#include <Circle.h>

InGameState::InGameState(StateManager* p_parent, IODevice* p_io, bool p_reset): State(p_parent)
{
	m_io = p_io;
	if (m_io)
	{
		m_factory = new GOFactory(p_io);
		m_tileMap = NULL;
		m_stats = NULL;
		m_currentMap = 0;
		if (p_reset)
			restart();
	}
}
InGameState::~InGameState()
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
	}
}

bool InGameState::onEntry()
{
	restart();
	return true;
}

void InGameState::update(float p_dt)
{
	if (m_io)
	{
		InputInfo input = m_io->fetchInput();
		
		if (m_stats->getNumPills() < 1)
		{
			//m_parent->terminate();
			m_currentMap = (m_currentMap+1) % 2;
			restart();
			return;
		}

		for (unsigned int index = 0; index < m_gameObjects.size(); index++)
		{
			m_gameObjects[index]->update(p_dt, input);
		};

		checkDynamicCollision();
	
		m_stats->update(p_dt);

		int elapsed = m_stats->getGameTimer()->getElapsedTime();

		stringstream ss;

		ss << elapsed;

		string text = "Elapsed Game Time: " + ss.str() + " seconds";

		m_io->setWindowText(text);

		if (input.keys[InputInfo::SPACE] == InputInfo::KEYRELEASED)
		{
			//m_parent->requestStateChange(m_parent->getMenuState());
			restart();
			return;
		}
		if(input.keys[InputInfo::ESC] == InputInfo::KEYPRESSED || !m_io->isRunning())
		{
			m_parent->terminate();
		}
	}
}

void InGameState::draw(float p_dt)
{
}

bool InGameState::checkDynamicCollision()
{
	Circle avatarBC(m_avatar->getPostion(), m_avatar->getRadius());

	bool collision = false;
	for(unsigned int index = 0; index < m_monsters.size(); index++)
	{
		Monster* monster = m_monsters.at(index);
		if (!monster->isDead())
		{
			Circle monsterBC(monster->getPostion(),monster->getRadius());

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
	}

	return collision;
}
void InGameState::restart()
{
	if (m_io)
	{
		m_io->clearSpriteInfos();
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			delete m_gameObjects[i];
		}
		m_gameObjects.clear();
		m_monsters.clear();
		if (m_tileMap)
			delete m_tileMap;
		if (m_stats)
			delete m_stats;

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
	}
}