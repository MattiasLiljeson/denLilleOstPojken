#include "AI.h"
#include "Monster.h"

AI::AI(Monster* p_master, Avatar* p_avatar, GameStats* p_gameStats, Tilemap* p_tilemap)
{
	m_master	= p_master;
	m_avatar	= p_avatar;
	m_gameStats = p_gameStats;
	m_tilemap	= p_tilemap;
	m_elapsedTime		= 0; 
}

AI::~AI()
{

}

void AI::update(float p_deltaTime)
{
	//Don't callculate AI decision every frame.
	m_elapsedTime += p_deltaTime;
}

void AI::findTarget()
{
	if(m_elapsedTime>0.5f)
	{
		// Adjusting the chance that a decisions is taken
		if(rand() % 100 <= 25)
		{
			m_elapsedTime = 0;
			
			// Check with if it's a good idea to chase the avatar or not
			if(shouldChaseTarget())
				chaseTarget();
			else
				fleeFromTarget();
		}
		// If it was not selected the AI will not take decisions for a while
		else
		{
			m_elapsedTime -= m_elapsedTime*0.2f;
		}
	}

	//Do something else when a new AI decision is not avaiable, e.g continue
	else
		return;
}

bool AI::shouldChaseTarget()
{
	// Check if various effects are active that makes the avatar fearsome!
	if(m_gameStats->isSuperMode())
		return false;
	
	return true;
}
void AI::chaseTarget()
{
	Tile* goal = m_avatar->getCurrentTile();
	m_master->FindPath(m_master->getCurrentTile(),goal);
}
void AI::fleeFromTarget()
{
	TilePosition fleeFromTile = m_avatar->getCurrentTile()->getTilePosition();
	TilePosition currentTile = m_master->getCurrentTile()->getTilePosition();

	int xDistance = abs(currentTile.x-fleeFromTile.x);
	int yDistance = abs(currentTile.y-fleeFromTile.y);

	xDistance = m_tilemap->getWidth() - xDistance;
	yDistance = m_tilemap->getWidth() - yDistance;
	
	int fleeDirX;
	int fleeDirY;

	if(randBool())
		fleeDirX = 1;
	else
		fleeDirX = -1;

	if(randBool())
		fleeDirY = 1;
	else
		fleeDirY = -1;

	xDistance = xDistance*fleeDirX;
	yDistance = yDistance*fleeDirY;

	if(xDistance < 0)
		xDistance = 0;
	else if(xDistance >= m_tilemap->getWidth())
		xDistance = m_tilemap->getWidth()-1;

	if(yDistance < 0)
		yDistance = 0;
	else if(yDistance >= m_tilemap->getHeight())
		yDistance = m_tilemap->getHeight()-1;

	TilePosition goalTP = TilePosition(xDistance,yDistance);
	Tile* goalT = m_tilemap->getTile(goalTP);

	m_master->FindPath(m_master->getCurrentTile(), goalT);
}
bool AI::randBool()
{
	return rand() % 2;
}