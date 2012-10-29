
#ifndef MENUSUBSTATEFACTORY_H
#define MENUSUBSTATEFACTORY_H

#include "GOFactory.h"
#include "MenuItem.h"
#include "MenuItemProperties.h"
#include "StateManager.h"

#include "MenuSubStateManager.h"
#include "MenuSubState.h"
#include "MainSubState.h"
#include "LevelSelectSubState.h"
#include "HighscoreSubState.h"
#include "CreditsSubState.h"
#include "ExitSubState.h"
#include <vector>
#include <string>

using namespace std;

class MenuSubStateManager;
class MenuSubState;

class MenuSubStateFactory
{
private:
	GOFactory* m_gof;
	MenuSubStateManager* m_manager;

public:
	MenuSubStateFactory( GOFactory* p_gof, MenuSubStateManager* p_manager );
	~MenuSubStateFactory();
	MenuSubState* createMain();
	MenuSubState* createLevelSelect( vector<MapData> p_maps );
	MenuSubState* createHighscore();
	MenuSubState* createCredits();
	MenuSubState* createExit();
	void initMenu(MenuSubState* p_menu);
	vector<MenuItem*> createItems( MenuItemProperties p_properties,
		vector<string> p_texts );
};
#endif // MENUSUBSTATEFACTORY_H