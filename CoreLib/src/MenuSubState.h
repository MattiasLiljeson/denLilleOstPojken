#ifndef MENUSUBSTATE_H
#define MENUSUBSTATE_H


#include <vector>
#include "GOFactory.h"
#include "MenuItem.h"
#include "MapHeader.h"

using namespace std;

struct HighScoreItem
{
	int score;
	bool operator < (const HighScoreItem& p_other) const
	{
		return score > p_other.score;
	}
};

struct MenuSubState
{
	// As the menu is rendered with 0.0 - 1.0 these small variables makes it
	// possible to define sizes, positions etc using fullHD as a reference
	float fw;
	float fh;
	fVector3 m_firstItemPos;
	fVector2 m_itemSize;
	fVector2 m_itemTextOffset;
	fVector2 m_itemFontSize;
	float m_itemDistance;
	string m_itemBackgroundTexturePath;

	GOFactory*			m_goFactory;
	vector<string>		m_texts;
	vector<MenuItem*>	m_items;
	int m_currItem;

	vector<MapData>*	m_maps;
	vector<HighScoreItem>* m_highscore;

	enum { MENU_MAIN, MENU_LEVEL_SELECT, MENU_HIGHSCORE, MENU_CREDITS, MENU_EXIT, NUM_MENUS };
	// Main menu
	enum { MM_LEVEL_SELECT, MM_HIGHSCORE, MM_CREDITS, MM_EXIT, MM_NUM_ITEMS };
	// Level Select
	enum { LS_MAIN, LS_NUM_ITEMS };
	// Highscore
	enum { HS_MAIN, HS_NUM_ITEMS };
	// Credits
	enum { CR_MAIN, CR_NUM_ITEMS };
	// Exit
	enum { EX_YES, EX_NO, EX_NUM_ITEMS };

	MenuSubState( vector<HighScoreItem>* p_highscore, vector<MapData>* p_maps, int p_type, GOFactory* p_goFactory);
	~MenuSubState();
	
	void clear();
	void setToMain();
	void setToLevelSelect();
	void setToHighscore();
	void setToCredits();
	void setToExit();
	void createItems();

	void activate();
	void deActivate();
	void setFirstSelectable();
	void setAllSelectable();
	void setAllUnSelectable();
};

#endif
