#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Timer.h"
#include "IIOContext.h"
#include "InputInfo.h"
#include "IO_.h"
#include "GameObject.h"

using namespace std;

class Game
{
public:
	Game(Timer* p_timer, IIOContext* p_context);
	~Game();

	int run();

private:
	Timer*				m_timer;
	IO*					m_io;
	bool				m_running;
	vector<GameObject>	m_gameObjects;

	int update(float p_deltaTime, InputInfo p_inputInfo);
};

#endif