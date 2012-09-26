#ifndef GAME_H
#define GAME_H

#include "StateManager.h"
#include <iostream>

using namespace std;

class Game
{
private:
	StateManager m_stateManager;
public:
	Game();
	void update(float p_dt);
	void draw(float p_dt);
};

#endif