#ifndef LEVELSELECTSUBSTATE_H
#define LEVELSELECTSUBSTATE_H

#include "StateManager.h"
#include <vector>

#include "MenuSubStateInterface.h"
#include "MenuSubStateManager.h"

using namespace std;

class LevelSelectSubState : public MenuSubStateInterface
{
public:
	enum { LS_MAIN, LS_NUM_ITEMS };

	LevelSelectSubState();
	~LevelSelectSubState();
	virtual void selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager );
	void escBtn( int p_currItemIdx, MenuSubStateManager* p_manager );
};

#endif // LEVELSELECTSUBSTATE_H
