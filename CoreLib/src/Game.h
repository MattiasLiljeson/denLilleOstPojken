#ifndef GAME_H
#define GAME_H

#ifndef _WIN32
#include <time.h>
#include <stdlib.h>
#endif

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
#include <sstream>

using namespace std;

class Game
{
private:
	Timer*				m_timer;
	IODevice*			m_io;
	bool				m_running;

	StateManager* m_stateManager;


public:
	Game();
	Game(Timer* p_timer, IOContext* p_context);
	virtual ~Game();
	int run();

};

#endif
