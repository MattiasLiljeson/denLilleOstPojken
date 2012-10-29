#ifndef MENUSUBSTATEINTERFACE_H
#define MENUSUBSTATEINTERFACE_H

//#include "MenuSubStateManager.h"

class MenuSubStateManager;

class MenuSubStateInterface
{
public:
	virtual void selectBtn( int p_currItemIdx, MenuSubStateManager* p_manager )
	{
	}

	virtual void escBtn( int p_currItemIdx, MenuSubStateManager* p_manager )
	{
		//p_manager->reqMenuChange( MenuSubStateManager::MENU_MAIN );
	}

};

#endif // MENUSUBSTATEINTERFACE_H