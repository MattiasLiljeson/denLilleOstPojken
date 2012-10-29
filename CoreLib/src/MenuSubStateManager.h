#ifndef MENUSUBSTATEMANAGER_H
#define MENUSUBSTATEMANAGER_H

#include <vector>
#include "InGameState.h"
#include "MapHeader.h"
#include "MenuState.h"
#include "MenuSubState.h"

using namespace std;

class MenuState;
class MenuSubState;

class MenuSubStateManager
{
private:
	MenuState* m_parent;
	vector<MenuSubState*> m_menus;

	int m_currMenu;

public:
	enum { MENU_MAIN, MENU_LEVEL_SELECT, MENU_HIGHSCORE, MENU_CREDITS, MENU_EXIT, NUM_MENUS };

	MenuSubStateManager( MenuState* p_parent );
	~MenuSubStateManager();
	void reqMenuChange( int p_state );
	void handleInput( InputInfo p_input );
	void addMenu( MenuSubState* p_menu, int p_type );
	void update( float p_dt );
	void terminateGame();
	void setCurrentMap( int p_mapIdx );
};
#endif // MENUSUBSTATEMANAGER_H