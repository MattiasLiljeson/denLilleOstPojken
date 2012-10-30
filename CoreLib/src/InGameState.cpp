#include "InGameState.h"
#include "StateManager.h"
#include "Game.h"
#include <Circle.h>

InGameState::InGameState(StateManager* p_parent, IODevice* p_io, vector<MapData> p_maps, bool p_reset): State(p_parent)
{
	m_io = p_io;
	m_maps = p_maps;
	m_currentMap = 0;
	m_desiredMap = -1;
	m_factory = new GOFactory(m_io);
	m_avatar	= NULL;
	m_gui		= NULL;
	m_tileMap	= NULL;
	m_stats		= NULL;
	m_startTile = NULL;
	m_backgroundMusic = NULL;
}
InGameState::~InGameState()
{
	if (m_factory)
	{
		delete m_factory;
		m_factory = NULL;
	}
	onExit();
}
bool InGameState::onEntry()
{
	if (!m_resourcesAllocated)
	{
		if (m_io)
		{
			m_tileMap = NULL;
			m_stats = NULL;
			m_currentMap = 0;
			m_gui = NULL;
			m_parent->getCommonResources()->totalScore = 0;
		}
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
			if (m_gui)
				delete m_gui;

			if (m_backgroundMusic)
			{
				m_backgroundMusic->deleted = true;
			}
		}
		m_resourcesAllocated=false;
	}

	return true;
}

void InGameState::update(float p_dt)
{
	if(m_desiredMap != -1)
	{
		m_currentMap = m_desiredMap;
		m_desiredMap = -1;
		restart();
	}

	if (m_io)
	{
		InputInfo input = m_io->fetchInput();

		if (input.keys[InputInfo::P_KEY] == InputInfo::KEYPRESSED)
		{
			m_paused = !m_paused;
			if (m_paused)
				m_gui->pause();
			else
				m_gui->unpause();
		}
		if (m_paused)
			p_dt = 0;

		if (input.keys[InputInfo::ESC] == InputInfo::KEYRELEASED)
		{
			if (m_stats->getNumLives() > 0)
			{
				m_parent->getCommonResources()->totalScore = 0;
				m_parent->requestStateChange(m_parent->getMenuState());
			}
			else
			{
				m_parent->getCommonResources()->totalScore = m_stats->getPreviousScore();
				m_parent->requestStateChange(m_parent->getGameOverState());
			}
		}
		if (m_stats->getNumPills() < 1 || m_stats->getNumLives() == 0)
		{
			//Victory
			if (m_stats->getNumPills() < 1)
			{
				updateOnVictory(p_dt, input);
			}
			else
			{
				//Defeat
				updateOnDefeat(p_dt, input);
			}
		}
		else
		{
			for (unsigned int index = 0; index < m_gameObjects.size(); index++)
			{
				m_gameObjects[index]->update(p_dt, input);
			};

			checkAndResolveDynamicCollision();

			checkAndResolveStaticCollision();
	
			if (m_stats)
			{
				m_stats->update(p_dt, input);
				if (m_stats->getActivatedItem() == 0)
				{
					Bomb* b = m_factory->CreateBomb(m_avatar->getClosestTile(), m_tileMap); 
					m_bombs.push_back(b);
					m_gameObjects.push_back(b);
				}
				if (m_stats->getGameTimer()->getElapsedTime() < 2)
				{
					// Edited by Johan:
					// made it readable.
					double arbitraryTimeValue =
						4 * (0.25 - m_stats->getGameTimer()->getElapsedTime());

					float timeFraction =
						(float)( max(0.0, arbitraryTimeValue) );

					m_io->fadeSceneToBlack(timeFraction);
				}
				if (m_stats->getGameTimer()->getElapsedTime() < 5)
					m_backgroundMusic->volume = 20 * (float)m_stats->getGameTimer()->getElapsedTime() / 5.0f;
				else
					m_backgroundMusic->volume = 20;
			}

			if (m_gui)
				m_gui->update(p_dt);

			int elapsed = (int)m_stats->getGameTimer()->getElapsedTime();

			stringstream ss;

			ss << elapsed;

			string text = "Elapsed Game Time: " + ss.str() + " seconds";

			m_io->setWindowText(text);

			if (m_avatar->isDead())
			{
				m_stats->loseLife();
				if (m_stats->getNumLives() > 0)
				{
					for (unsigned int i = 0; i < m_gameObjects.size(); i++)
					{
						m_gameObjects[i]->reset();
					}

					m_avatar->revive(m_startTile);
				}


			}
		}
	}
}

void InGameState::draw(float p_dt)
{
}

void InGameState::checkAndResolveDynamicCollision()
{
	Circle avatarBC(m_avatar->getPostion(), m_avatar->getRadius() / 4);

	for(unsigned int index = 0; index < m_monsters.size(); index++)
	{
		Monster* monster = m_monsters.at(index);
		if (!monster->isDead())
		{
			Circle monsterBC(monster->getPostion(),monster->getRadius() / 4);

			if(avatarBC.collidesWith(monsterBC))
			{
				if (m_stats->isSuperMode())
				{
					monster->kill();
					m_stats->addScore(MONSTER_KILLED);
				}
				else
					m_avatar->kill();
			}
		}
		for (unsigned int bomb = 0; bomb < m_bombs.size(); bomb++)
		{
			if (m_bombs[bomb]->isColliding(monster) && !monster->isDead())
			{
				monster->kill();
				m_stats->addScore(MONSTER_KILLED);
			}
		}
	}

	for (unsigned int bomb = 0; bomb < m_bombs.size(); bomb++)
	{
		if (m_bombs[bomb]->isColliding(m_avatar))
		{
			m_avatar->kill();
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
				m_avatar->kill();
			}
		}
	}
}

void InGameState::checkAndResolveStaticCollision()
{
	Tile* tileAheadOfAvatar = NULL;
	Tile* avatarTile;
	TilePosition tilePositionAheadOfAvatar;
	TilePosition avatarTilePosition;

	avatarTile = m_avatar->getCurrentTile();
	avatarTilePosition = avatarTile->getTilePosition();
	int avatarDirection = m_avatar->getDirection();
	
	tilePositionAheadOfAvatar = avatarTilePosition;
	if( avatarDirection == Direction::LEFT )
		tilePositionAheadOfAvatar.x -= 1;
	else if( avatarDirection == Direction::RIGHT )
		tilePositionAheadOfAvatar.x += 1;
	else if( avatarDirection == Direction::DOWN )
		tilePositionAheadOfAvatar.y -= 1;
	else if( avatarDirection == Direction::UP )
		tilePositionAheadOfAvatar.y += 1;
	
	tileAheadOfAvatar = m_tileMap->getTile( tilePositionAheadOfAvatar );

	if( tileAheadOfAvatar != NULL )
	{
		// There is a tile ahead of avatar.
		Collectable* collectableAheadOfAvatar = tileAheadOfAvatar->getCollectable();
		if( collectableAheadOfAvatar != NULL )
		{
			Circle avatarBC(m_avatar->getPostion(), m_avatar->getRadius() / 4);

			Circle pillBC(collectableAheadOfAvatar->getPostion(),
				collectableAheadOfAvatar->getRadius() / 4);

			if( avatarBC.collidesWith( pillBC ) )
			{
				collectableAheadOfAvatar->consume();
			}
		}

	}

}

void InGameState::restart()
{
	if (m_io)
	{
		m_victoryTime = 0;
		m_defeatTime = 0;
		m_toneOutTimer = 0;
		m_io->clearSpriteInfos();
		for (unsigned int i = 0; i < m_gameObjects.size(); i++)
		{
			if( m_gameObjects[i] != NULL)
			{
				delete m_gameObjects[i];
				m_gameObjects[i] = NULL;
			}
		}
		m_gameObjects.clear();
		m_monsters.clear();
		m_bombs.clear();
		if (m_tileMap)
		{
			delete m_tileMap;
			m_tileMap = NULL;
		}
		if (m_gui)
		{
			delete m_gui;
			m_gui = NULL;
		}

		m_tileMap	= 0;
		MapLoader mapParser;

		int tscore = 0;
		if (m_stats)
		{
			tscore = m_stats->getTotalScore();
			delete m_stats;
		}
		m_stats = new GameStats(m_parent->getNewTimerInstance(), m_maps[m_currentMap].parTime, tscore);

		stringstream ss;
		ss << m_currentMap;
		string mapString = "../Maps/" + m_maps[m_currentMap].filename;
		mapParser.parseMap(mapString, m_io, m_stats, m_factory);

		m_tileMap = mapParser.getTileMap();
		m_gameObjects = mapParser.getGameObjects();
		m_avatar = mapParser.getAvatar();
		m_monsters = mapParser.getMonsters();
		m_traps = mapParser.getTraps();
		m_gui = mapParser.getGUI();
		m_paused = false;

		if (m_avatar)
			m_startTile = m_avatar->getCurrentTile();

		m_io->fadeSceneToBlack(1.0f);
	}

	m_parent->stopMainTimer();
	m_parent->startMainTimer();

	//Ugly - Should be corrected. Leave for now
	if (m_backgroundMusic)
	{
		m_backgroundMusic->deleted = true;
	}
	m_backgroundMusic = new SoundInfo();
	m_backgroundMusic->id = "../Sounds/Music/" + m_maps[m_currentMap].backgroundMusic;
	m_backgroundMusic->play = true;
	m_backgroundMusic->volume = 0;
	m_io->addSong(m_backgroundMusic);

	//ANTON FIX!
	//Makes sure the game starts at time 0
	m_stats->getGameTimer()->stop();
	m_stats->getGameTimer()->start();
}

int InGameState::setCurrentMap( MapData p_map )
{
	bool found =  false;
	unsigned int idx = 0;
	while( !found && idx<m_maps.size() )
	{
		if(m_maps[idx].filename == p_map.filename)
			found = true;
	}

	if(found)
		return setCurrentMap(idx);
	else
		return GAME_FAIL;
}

int InGameState::setCurrentMap( int p_mapIdx )
{
	if( (unsigned int)p_mapIdx < m_maps.size() )
	{
		m_desiredMap = p_mapIdx;
		//restart();
		return GAME_OK;
	}
	else
	{
		return GAME_FAIL;
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
void InGameState::updateOnVictory(float p_dt, InputInfo p_input)
{
	float timings[6] =
	{
		3.0f,	// Finished
		2.4f,	// Total score
		2.1f,	// Multiplier
		1.8f,	// Base score
		1.5f,	// Victory time
		0.0f	// Fade out
	};

	if( p_input.keys[InputInfo::ENTER] == InputInfo::KEYPRESSED ||
		p_input.keys[InputInfo::SPACE] == InputInfo::KEYPRESSED )
	{
		if( m_victoryTime >= 3 )
		{
			if (m_toneOutTimer == 0)
				m_toneOutTimer += p_dt;
		}
		else
		{
			for( int i = 1; i < 6; i++)
			{
				if( m_victoryTime > timings[i] )
				{
					m_victoryTime = timings[i - 1];
					break;
				}
			}
		}
	}
	else if (m_victoryTime > 2.4f)
	{
		int totalScore = (int)(m_stats->getScore() * m_stats->getMultiplier());
		m_gui->showTotalScore(totalScore);
	}
	else if (m_victoryTime > 2.1f)
	{
		m_gui->showMultiplier(m_stats->getMultiplier());
	}
	else if (m_victoryTime > 1.8f)
	{
		m_gui->showBaseScore(m_stats->getScore());
	}
	else if (m_victoryTime > 1.5f)
	{
		m_gui->showVictory();
	}
	m_victoryTime+= p_dt;
	m_io->toneSceneBlackAndWhite(min(m_victoryTime / 1, 1.0f));

	if (m_toneOutTimer > 0)
	{
		m_toneOutTimer += p_dt;
		m_io->fadeSceneToBlack(min(m_toneOutTimer*4, 1.0f));
		if (m_toneOutTimer > 0.25f)
		{
			if ( (unsigned int)(m_currentMap) < m_maps.size() - 1 )
			{
				m_currentMap = m_currentMap+1;

				if (m_parent->getCommonResources()->unlockedLevels < m_currentMap+1)
				{
					m_parent->getCommonResources()->unlockedLevels = m_currentMap+1;
				}
				restart();
			}
			else
			{
				m_parent->getCommonResources()->totalScore = m_stats->getTotalScore();
				m_parent->requestStateChange(m_parent->getVictoryState());
			}
			return;
		}
	}
}
void InGameState::updateOnDefeat(float p_dt, InputInfo p_input)
{
	m_defeatTime += p_dt;
	m_io->toneSceneBlackAndWhite(min(m_defeatTime / 1, 1.0f));
	
	if(p_input.keys[InputInfo::ENTER] == InputInfo::KEYPRESSED && m_defeatTime > 3)
	{
		if (m_toneOutTimer == 0)
			m_toneOutTimer += p_dt;
	}
	else if (m_defeatTime > 2.1f)
	{
		m_gui->showContinue();
	}
	else if (m_defeatTime > 1.8f)
	{
		m_gui->showCost();
	}
	else if (m_defeatTime > 1.5f)
	{
		m_gui->showDefeat();
	}
	if (m_toneOutTimer > 0)
	{
		m_toneOutTimer += p_dt;
		m_io->fadeSceneToBlack(min(m_toneOutTimer*4, 1.0f));
		if (m_toneOutTimer > 0.25f)
		{
			m_stats->addScore(-m_stats->getScore());
			m_stats->halvePreviousScore();
			restart();
		}
	}
}