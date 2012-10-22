#ifndef MENUSUBSTATE_H
#define MENUSUBSTATE_H

#include <vector>
#include "GOFactory.h"
#include "MenuItem.h"

using namespace std;

struct MenuSubState
{
	float fw;
	float fh;

	GOFactory*			m_goFactory;
	vector<string>		m_texts;
	vector<MenuItem*>	m_items;

	enum { MENU_MAIN, MENU_LEVEL_SELECT, MENU_HIGHSCORE, MENU_CREDITS, MENU_EXIT, NUM_MENUS };
	// Main menu
	enum { MM_LEVEL_SELECT, MM_HIGHSCORE, MM_CREDITS, MM_EXIT, MM_NUM_ITEMS };
	// Level Select
	enum { LS_MAIN, LS_START_LEVEL, LS_NUM_ITEMS };
	// High score
	// Credits
	// Exit
	enum { EX_YES, EX_NO, EX_NUM_ITEMS };

	MenuSubState( int p_type, GOFactory* p_goFactory );
	~MenuSubState();
	
	void clear();
	void setToMain();
	void setToLevelSelect();
	void setToHighscore();
	void setToCredits();
	void setToExit();

	void activate();
	void deActivate();
};

#endif