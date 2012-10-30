#ifndef HIGHSCORESUBSTATE_H
#define HIGHSCORESUBSTATE_H


//#include "DebugPrint.h"
#include "ToString.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "MenuSubState.h"
#include "MenuSubStateManager.h"

class MenuSubStateManager;

using namespace std;

class HighscoreSubState : public MenuSubStateInterface
{
public:
	enum { HS_MAIN, HS_NUM_ITEMS };
	HighscoreSubState();
	~HighscoreSubState();

	virtual void selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu );
	void escBtn( int p_currItemIdx, MenuSubStateManager* p_manager, MenuSubState* p_menu );
};

#endif // HIGHSCORESUBSTATE_H
