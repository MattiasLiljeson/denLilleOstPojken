#ifndef INGAMESTATE_H
#define INGAMESTATE_H

#include "State.h"

class InGameState: public State
{
private:
	IODevice*			m_io;
	vector<GameObject*>	m_gameObjects;
	MapLoader*			m_mapParser;

	//Temp
	Tilemap* m_tileMap;
public:
	InGameState(StateManager* p_parent, IODevice* p_io);
	virtual ~InGameState();
	void update(float p_dt);
	void draw(float p_dt);
};

#endif
