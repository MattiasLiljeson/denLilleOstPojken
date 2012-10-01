#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Timer.h"
#include "IOContext.h"
#include "InputInfo.h"
#include "IODevice.h"
#include "GameObject.h"
#include "Tilemap.h"
#include "Pill.h"
#include "Monster.h"
#include "MapLoader.h"
#include "StateManager.h"
#include "GameStats.h"

using namespace std;

class Game
{
private:
	Timer*				m_timer;
	IODevice*			m_io;
	bool				m_running;
	vector<GameObject*>	m_gameObjects;
	MapLoader*			m_mapParser;
	GameStats*			m_gameStats;

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