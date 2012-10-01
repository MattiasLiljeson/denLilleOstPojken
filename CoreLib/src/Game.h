#ifndef GAME_H
#define GAME_H

#include "StateManager.h"

using namespace std;

class Game
{
private:
	Timer*				m_timer;
	IODevice*			m_io;
	bool				m_running;
	vector<GameObject*>	m_gameObjects;
	LoadMap*			m_mapParser;

	//Temp
	Tilemap* m_tileMap;

	StateManager* m_stateManager;


public:
	Game();
	Game(Timer* p_timer, IOContext* p_context);
	virtual ~Game();

	int run();

private:
	int update(float p_deltaTime, InputInfo p_inputInfo);

};

#endif