#ifndef MENUSUBSTATE_H
#define MENUSUBSTATE_H

#include "fVector2.h"
#include "fVector3.h"
#include "MenuItem.h"
#include "MenuItemProperties.h"
#include "MenuSubStateManager.h"
#include <vector>
#include <string>

using namespace std;

class MenuSubStateManager;

class MenuSubState
{
protected:
	//GOFactory* m_goFactory;
	//MenuState* m_menuState;
	MenuSubStateManager* m_manager;
	MenuItemProperties m_properties;

	// As the menu is rendered with 0.0 - 1.0 these small variables makes
	// it possible to define sizes, positions etc using fullHD as a
	// reference
	float fw;
	float fh;

	vector<string>		m_texts;
	vector<MenuItem*>	m_items;
	int m_currItemIdx;

protected:
	void nextItem();
	void prevItem();
	void nextSelectableItem();
	void prevSelectableItem();

public:
	MenuSubState( MenuSubStateManager* m_manager );
	virtual ~MenuSubState();
	
	virtual void upBtn();
	virtual void downBtn();
	virtual void selectBtn() = 0;
	virtual void escBtn();

	void update( float p_dt );

	void clear();
	vector<string> getTexts();
	MenuItemProperties getProperties();
	void addItems(vector<MenuItem*> p_items);

	virtual void onEntry();
	virtual void onExit();

	void setFirstSelectable();
	void setAllSelectable();
	void setAllNonSelectable();
	void setAllVisible();
	void setAllNonVisible();
};

#endif