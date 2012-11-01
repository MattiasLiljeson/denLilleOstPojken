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
	vector<MenuItem*> m_items;

	int m_currItemIdx;

	int m_currState;
	int m_nextMenu;
	float m_stateTimer;
	float m_introTime;
	float m_outroTime;
	float m_selectedTime;
	
	SoundInfo* m_menuBackSnd;
	SoundInfo* m_menuNavigatonSnd;
	SoundInfo* m_itemSelectSnd;

public:
	enum { IN_ENTRY, IN_MENU, ITEM_SELECTED, IN_EXIT };

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
	void updateInEntry( float p_dt );
	void updateInMenu( float p_dt );
	void updateItemSelected( float p_dt );
	void updateInExit( float p_dt );

	void setBehaviour( MenuSubStateInterface* p_behaviour );
	void setProperties( MenuItemProperties p_properties );
	MenuItemProperties getProperties();
	void addItems(vector<MenuItem*> p_items);
	void setMenuBackSnd( SoundInfo* p_menuBackSnd);
	void setMenuNavigatonSnd( SoundInfo* p_menuNavigatonSnd);
	void setItemSelectSnd( SoundInfo* p_itemSelectSnd );

	void setNextMenu( int p_menu );
	void setItemSelected();
	void setInExit();
	void setFirstSelectable();
	void setAllSelectable();
	void setAllNonSelectable();
	void setAllVisible();
	void setAllNonVisible();
	void setSelectable( int p_idx, bool p_selectable );

	bool playSound( SoundInfo* p_sound );
};

#endif