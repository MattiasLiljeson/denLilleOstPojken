#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GOFactory.h"
#include "MenuItem.h"
#include "SoundInfo.h"
#include "State.h"
#include "TextArea.h"
#include <vector>
#include <cmath>
#include "MenuSubState.h"
#include "MapHeader.h"
#include "InGameState.h"

using namespace std;

class MenuState: public State
{
private:
	IODevice* m_io;
	GOFactory* m_factory;

	// Menus
	vector<MenuSubState*> m_menus;
	unsigned int m_currMenu;
	unsigned int m_currItemIdx;

	float m_totTime;
	MenuItem* m_bgItem;
	SoundInfo* m_itemSelectSnd;
	vector<MapData>	m_maps;

private:
	//utility functions
	void resetItemOffset( int p_idx );
	void nextItem();
	void prevItem();
	void setCurrMenu( int p_menu );

	void selectMmItem();
	void selectLsItem();
	void selectExState();

	bool playSound();

	void initMenuItems();

public:
	MenuState(StateManager* p_parent, IODevice* p_io, vector<MapData> p_maps);
	virtual ~MenuState();
	void update(float p_dt);
	void draw(float p_dt);
	void handleInput(InputInfo p_input);
	bool onEntry();
	bool onExit();
};
#endif