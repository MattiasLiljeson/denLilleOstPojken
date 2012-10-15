#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "State.h"
#include "GameStats.h"

class InGameState: public State
{
private:
	IODevice*			m_io;
	vector<GameObject*>	m_gameObjects;
	Avatar*				m_avatar;
	vector<Monster*>	m_monsters;
	GOFactory*			m_factory;

	//Temp
	Tilemap* m_tileMap;
	GameStats* m_stats;
	int	m_currentMap;
public:
	InGameState(StateManager* p_parent, IODevice* p_io, bool p_reset = false);
	virtual ~InGameState();
	void update(float p_dt);
	void draw(float p_dt);
	bool checkDynamicCollision();
	void restart();
	bool onEntry();
	bool onExit();
};

#endif
