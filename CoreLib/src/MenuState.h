#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GOFactory.h"
#include "InGameState.h"
#include "MapHeader.h"
#include "MenuItem.h"
#include "MenuSubStateFactory.h"
#include "MenuSubStateManager.h"
#include "SoundInfo.h"
#include "State.h"
#include "TextArea.h"
#include <cmath>
#include <vector>

class MenuSubStateManager;
class MenuSubStateFactory;

using namespace std;

class MenuState: public State
{
private:
	IODevice* m_io;
	GOFactory* m_gof;
	MenuSubStateFactory* m_menuFactory;

	// Menus
	MenuSubStateManager* m_manager;

	vector<MapData> m_maps;
	MenuItem* m_bgItem;
	//New - To add fade functionality
	int m_requestedLevel;
	float m_requestedTimer;

	//Music
	SoundInfo* m_backgroundMusic;

private:
	void createMenus();
	void removeMenus();

public:
	MenuState(StateManager* p_parent, IODevice* p_io, vector<MapData> p_maps);
	virtual ~MenuState();

	bool onEntry();
	bool onExit();

	void update( float p_dt );
	void draw( float p_dt );
	void handleInput( InputInfo p_input );
	void reqMenuChange( int p_menu );
	StateManager* getParent();
};

#endif
