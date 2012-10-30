#ifndef MENUSUBSTATE_H
#define MENUSUBSTATE_H

#include "fVector2.h"
#include "fVector3.h"
#include "MenuItem.h"
#include "MenuItemProperties.h"
#include "MenuSubStateManager.h"
#include "MenuSubStateInterface.h"
#include <vector>
#include <string>

using namespace std;

class MenuSubStateInterface;
class MenuSubStateManager;

class MenuSubState
{
protected:
	MenuSubStateManager* m_manager;
	MenuItemProperties m_properties;

	MenuSubStateInterface* m_behaviour;
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
	void clear();
	
	virtual void upBtn();
	virtual void downBtn();
	virtual void selectBtn();
	virtual void escBtn();

	virtual void onEntry();
	virtual void onExit();

	void update( float p_dt );

	//void setTexts( vector<string> p_texts );
	//vector<string> getTexts();
	void setBehaviour( MenuSubStateInterface* p_behaviour );
	void setProperties( MenuItemProperties p_properties );
	MenuItemProperties getProperties();
	void addItems(vector<MenuItem*> p_items);

	void setFirstSelectable();
	void setAllSelectable();
	void setAllNonSelectable();
	void setAllVisible();
	void setAllNonVisible();
};

#endif