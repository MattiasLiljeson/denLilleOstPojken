#ifndef LEVELSELECTSUBSTATE_H
#define LEVELSELECTSUBSTATE_H

#include "StateManager.h"
#include <vector>

#include "MenuSubState.h"

class StateManager;
class MenuSubStateManager;

class LevelSelectSubState : public MenuSubState
{
private:
	vector<MapData>	m_maps;

public:
	enum { LS_MAIN, LS_NUM_ITEMS };
	LevelSelectSubState( MenuSubStateManager* p_manager, vector<MapData> p_maps );
	~LevelSelectSubState();

	virtual void selectBtn();
};

#endif // LEVELSELECTSUBSTATE_H
