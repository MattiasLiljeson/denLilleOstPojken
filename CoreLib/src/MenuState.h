#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GOFactory.h"
#include "MenuItem.h"
#include "SoundInfo.h"
#include "State.h"
#include "TextArea.h"
#include <vector>
#include <cmath>
#include "MapHeader.h"

using namespace std;

class MenuState: public State
{
private:
	IODevice* m_io;

	float m_totTime;
	unsigned int m_currItemIdx;
	vector<MenuItem*> m_menuItems;
	MenuItem* m_bgItem;

	GOFactory* m_factory;

	SoundInfo* m_itemSelectSnd;
	vector<MapData>	m_maps;

public:
	// MI = menu item
	enum { MI_LEVEL_SELECT, MI_HIGHSCORE, MI_CREDITS, MI_EXIT };

private:
	//utility functions
	void nextItem();
	void prevItem();
	bool playSound();
	void indentItem( int p_idx, int p_amount );

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